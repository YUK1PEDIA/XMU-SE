class Lexer:
    def __init__(self, source_code):
        self.source_code = source_code + ' '  # 添加空格确保最后一个token被处理
        self.position = 0
        self.current_char = self.source_code[0] if self.source_code else None
        self.tokens = []
        self.line = 1
        self.column = 1
        self.keywords = {
            'const': 'CONST',
            'var': 'VAR',
            'procedure': 'PROCEDURE',
            'call': 'CALL',
            'begin': 'BEGIN',
            'end': 'END',
            'if': 'IF',
            'then': 'THEN',
            'while': 'WHILE',
            'do': 'DO',
            'odd': 'ODD',
            'read': 'READ',
            'write': 'WRITE'
        }
        self.operators = {
            '+': 'PLUS',
            '-': 'MINUS',
            '*': 'MULTIPLY',
            '/': 'DIVIDE',
            '=': 'EQUAL',
            '#': 'NOT_EQUAL',
            '<': 'LESS',
            '<=': 'LESS_EQUAL',
            '>': 'GREATER',
            '>=': 'GREATER_EQUAL',
            ':=': 'ASSIGN'
        }
        self.delimiters = {
            ',': 'COMMA',
            ';': 'SEMICOLON',
            '.': 'PERIOD',
            '(': 'LPAREN',
            ')': 'RPAREN'
        }

    def error(self, message):
        raise Exception(f"Lexer error at line {self.line}, column {self.column}: {message}")

    def advance(self):
        if self.current_char == '\n':
            self.line += 1
            self.column = 0
        
        self.position += 1
        if self.position < len(self.source_code):
            self.current_char = self.source_code[self.position]
            self.column += 1
        else:
            self.current_char = None

    def skip_whitespace(self):
        while self.current_char is not None and self.current_char.isspace():
            self.advance()

    def skip_comment(self):
        while self.current_char is not None and self.current_char != '}':
            self.advance()
        if self.current_char is None:
            self.error("Unterminated comment")
        self.advance()  # 跳过结束的 '}'

    def get_number(self):
        result = ''
        while self.current_char is not None and self.current_char.isdigit():
            result += self.current_char
            self.advance()
        return ('NUMBER', int(result))

    def get_identifier(self):
        result = ''
        while self.current_char is not None and (self.current_char.isalnum() or self.current_char == '_'):
            result += self.current_char
            self.advance()
        
        # 将标识符转换为小写进行关键字匹配
        lower_result = result.lower()
        if lower_result in self.keywords:
            return (self.keywords[lower_result], result)
        return ('IDENTIFIER', result)

    def get_operator(self):
        op = self.current_char
        start_position = self.position
        start_line = self.line
        start_column = self.column
        
        self.advance()
        
        # 先检查双字符操作符
        if op == ':':
            if self.current_char == '=':
                self.advance()
                return ('ASSIGN', ':=')
            else:
                # 如果':'后面不是'='，则报错
                self.position = start_position
                self.line = start_line
                self.column = start_column
                self.current_char = op
                self.error(f"Unexpected character: '{op}'. Did you mean ':='?")
        
        # 检查其他双字符操作符
        if op == '<' and self.current_char == '=':
            self.advance()
            return ('LESS_EQUAL', '<=')
        if op == '>' and self.current_char == '=':
            self.advance()
            return ('GREATER_EQUAL', '>=')
        
        # 单字符操作符
        if op in self.operators:
            return (self.operators[op], op)
        
        self.error(f"Unknown operator: {op}")

    def tokenize(self):
        try:
            while self.current_char is not None:
                if self.current_char.isspace():
                    self.skip_whitespace()
                    continue
                
                if self.current_char == '{':
                    self.advance()
                    self.skip_comment()
                    continue
                
                # 检查双字符操作符的起始字符
                if self.current_char in ['<', '>', ':']:
                    token = self.get_operator()
                    self.tokens.append(token)
                    continue
                
                if self.current_char.isdigit():
                    token = self.get_number()
                    self.tokens.append(token)
                    continue
                
                if self.current_char.isalpha() or self.current_char == '_':
                    token = self.get_identifier()
                    self.tokens.append(token)
                    continue
                
                # 处理单字符操作符
                if self.current_char in self.operators:
                    token = (self.operators[self.current_char], self.current_char)
                    self.advance()
                    self.tokens.append(token)
                    continue
                
                if self.current_char in self.delimiters:
                    token = (self.delimiters[self.current_char], self.current_char)
                    self.advance()
                    self.tokens.append(token)
                    continue
                
                self.error(f"Unexpected character: '{self.current_char}'")
            
            # 添加结束标记
            self.tokens.append(('EOF', 'EOF'))
            return self.tokens
        except Exception as e:
            print(f"词法分析错误: {e}")
            return []
            