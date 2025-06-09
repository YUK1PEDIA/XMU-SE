from lexer import Lexer

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.current_token_index = 0
        if tokens:
            self.current_token = tokens[0]
        else:
            self.current_token = None
        self.symbol_table = {}  # 符号表：存储变量和常量
        self.procedures = {}    # 存储过程信息
        self.errors = []
        self.current_level = 0  # 当前嵌套层级
        self.next_address = 0   # 下一个可用地址
        self.proc_entry_counter = 0  # 新增：过程入口地址计数器

    def error(self, message):
        self.errors.append(f"语法错误: {message} (位置: {self.current_token})")
        self.advance()  # 尝试恢复

    def advance(self):
        self.current_token_index += 1
        if self.current_token_index < len(self.tokens):
            self.current_token = self.tokens[self.current_token_index]
        else:
            self.current_token = None

    def match(self, expected_type):
        if self.current_token and self.current_token[0] == expected_type:
            token = self.current_token
            self.advance()
            return token
        self.error(f"期望 {expected_type}，但得到 {self.current_token[0] if self.current_token else 'EOF'}")
        return None

    def program(self):
        """program = block ."""
        if not self.current_token:
            self.error("缺少程序内容")
            return ('empty',)
        
        block = self.block()
        self.match('PERIOD')
        return block

    def block(self):
        """block = [const-declaration] [var-declaration] {procedure-declaration} statement"""
        # 常量声明
        if self.current_token and self.current_token[0] == 'CONST':
            self.const_declaration()
        
        # 变量声明
        if self.current_token and self.current_token[0] == 'VAR':
            self.var_declaration()
        
        # 过程声明
        while self.current_token and self.current_token[0] == 'PROCEDURE':
            self.procedure_declaration()
        
        # 语句
        stmt = self.statement()
        return stmt

    def const_declaration(self):
        """const-declaration = CONST identifier = number {, identifier = number} ;"""
        self.match('CONST')
        while True:
            ident = self.match('IDENTIFIER')
            self.match('EQUAL')
            num = self.match('NUMBER')
            self.symbol_table[ident[1]] = ('CONST', num[1])  # 仅存储类型和值，无需地址
            if self.current_token and self.current_token[0] == 'COMMA':
                self.match('COMMA')
            else:
                break
        self.match('SEMICOLON')

    def var_declaration(self):
        """var-declaration = VAR identifier {, identifier} ;"""
        self.match('VAR')
        while True:
            ident = self.match('IDENTIFIER')
            self.symbol_table[ident[1]] = ('VAR', self.next_address)  # 存储类型和地址
            self.next_address += 1
            if self.current_token and self.current_token[0] == 'COMMA':
                self.match('COMMA')
            else:
                break
        self.match('SEMICOLON')

    def procedure_declaration(self):
        self.match('PROCEDURE')
        proc_name = self.match('IDENTIFIER')[1]
        self.match('SEMICOLON')
        
        # 记录过程入口地址（使用计数器模拟）
        entry_address = self.proc_entry_counter
        self.proc_entry_counter += 1  # 简单递增，实际需根据代码长度计算
        
        self.current_level += 1
        prev_symbol_table = self.symbol_table.copy()
        prev_next_address = self.next_address
        
        self.symbol_table = prev_symbol_table.copy()
        self.next_address = 0
        
        proc_block = self.block()
        self.match('SEMICOLON')
        
        self.procedures[proc_name] = {
            'level': self.current_level,
            'block': proc_block,
            'symbol_table': self.symbol_table.copy(),
            'local_vars_count': self.next_address,
            'entry': entry_address  # 新增：记录入口地址
        }
        
        self.symbol_table = prev_symbol_table
        self.next_address = prev_next_address
        self.current_level -= 1

    def statement(self):
        """statement = [identifier := expression]
                    | [CALL identifier]
                    | [BEGIN statement {; statement} END]
                    | [IF condition THEN statement]
                    | [WHILE condition DO statement]
                    | [READ identifier]
                    | [WRITE expression]
        """
        if not self.current_token:
            return ('empty',)
        
        token_type = self.current_token[0]
        
        if token_type == 'IDENTIFIER':
            ident = self.current_token[1]
            self.match('IDENTIFIER')
            self.match('ASSIGN')
            expr = self.expression()
            return ('assign', ident, expr)
        
        elif token_type == 'CALL':
            self.match('CALL')
            proc_name = self.match('IDENTIFIER')[1]
            return ('call', proc_name)
        
        elif token_type == 'BEGIN':
            self.match('BEGIN')
            statements = [self.statement()]
            while self.current_token and self.current_token[0] == 'SEMICOLON':
                self.match('SEMICOLON')
                if self.current_token and self.current_token[0] == 'END':
                    break  # 处理空语句序列的情况
                statements.append(self.statement())
            self.match('END')
            return ('begin', statements)
        
        elif token_type == 'IF':
            self.match('IF')
            cond = self.condition()
            self.match('THEN')
            stmt = self.statement()
            return ('if', cond, stmt)
        
        elif token_type == 'WHILE':
            self.match('WHILE')
            cond = self.condition()
            self.match('DO')
            stmt = self.statement()
            return ('while', cond, stmt)
        
        elif token_type == 'READ':
            self.match('READ')
            ident = self.match('IDENTIFIER')[1]
            return ('read', ident)
        
        elif token_type == 'WRITE':
            self.match('WRITE')
            expr = self.expression()
            return ('write', expr)
        
        else:
            return ('empty',)

    def condition(self):
        """condition = ODD expression | expression ( = | # | < | <= | > | >= ) expression"""
        if self.current_token and self.current_token[0] == 'ODD':
            self.match('ODD')
            expr = self.expression()
            return ('odd', expr)
        
        left = self.expression()
        op_token = self.current_token
        if op_token and op_token[0] in ['EQUAL', 'NOT_EQUAL', 'LESS', 'LESS_EQUAL', 'GREATER', 'GREATER_EQUAL']:
            self.advance()
            right = self.expression()
            return (op_token[0], left, right)
        
        self.error("期望比较运算符")
        return None

    def expression(self):
        """expression = [ + | - ] term { ( + | - ) term }"""
        sign = None
        if self.current_token and self.current_token[0] in ['PLUS', 'MINUS']:
            sign = self.current_token[0]
            self.advance()
        
        left = self.term()
        
        if sign == 'MINUS':
            left = ('negate', left)
        
        while self.current_token and self.current_token[0] in ['PLUS', 'MINUS']:
            op = self.current_token[0]
            self.advance()
            right = self.term()
            left = (op, left, right)
        
        return left

    def term(self):
        """term = factor { ( * | / ) factor }"""
        left = self.factor()
        while self.current_token and self.current_token[0] in ['MULTIPLY', 'DIVIDE']:
            op = self.current_token[0]
            self.advance()
            right = self.factor()
            left = (op, left, right)
        return left

    def factor(self):
        """factor = identifier | number | ( expression )"""
        if not self.current_token:
            self.error("期望标识符、数字或 '('")
            return ('number', 0)  # 返回默认值以避免崩溃
        
        token_type = self.current_token[0]
        if token_type == 'IDENTIFIER':
            ident = self.match('IDENTIFIER')[1]
            return ('identifier', ident)
        elif token_type == 'NUMBER':
            num = self.match('NUMBER')[1]
            return ('number', num)
        elif token_type == 'LPAREN':
            self.match('LPAREN')
            expr = self.expression()
            self.match('RPAREN')
            return expr
        else:
            self.error("期望标识符、数字或 '('")
            return ('number', 0)  # 返回默认值以避免崩溃

    def parse(self):
        if not self.tokens:
            self.error("空的token列表")
            return ('empty',)
        
        return self.program()
