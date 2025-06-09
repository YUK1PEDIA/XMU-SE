class CodeGenerator:
    def __init__(self, ast, symbol_table, procedures):
        self.ast = ast
        self.symbol_table = {}
        self.procedures = procedures
        self.code = []
        self.next_address = 0
        self.labels = {}
        self.next_label = 0
        
        # 正确解析二元组符号表
        for name, (kind, value) in symbol_table.items():  # 改为二元组解包
            if kind == 'VAR':
                self.symbol_table[name] = value  # 变量存储地址
            elif kind == 'CONST':
                self.symbol_table[name] = value  # 常量存储值
        

    def new_label(self):
        """生成新标签"""
        label = f"L{self.next_label}"
        self.next_label += 1
        return label

    def generate(self):
        # 分配全局变量空间
        global_vars = [name for name, info in self.symbol_table.items() if isinstance(info, int)]
        self.code.append(('INT', 0, len(global_vars)))
        
        # 生成主程序和过程代码（简化，假设过程入口已由 parser 分配）
        self.generate_block(self.ast)
        self.code.append(('OPR', 0, 0))  # 主程序结束
        
        return self.code

    def generate_block(self, block):
        """生成块的代码"""
        if block[0] == 'assign':
            _, ident, expr = block
            self.generate_expression(expr)
            addr = self.symbol_table.get(ident)
            if addr is not None:
                self.code.append(('STO', 0, addr))
            else:
                raise Exception(f"未定义的变量: {ident}")
        
        elif block[0] == 'call':
            _, proc_name = block
            proc_info = self.procedures.get(proc_name)
            if not proc_info:
                raise Exception(f"过程 {proc_name} 未定义")
            
            # 使用 parser 中记录的 entry 地址
            entry_addr = proc_info['entry']
            
            # 分配过程局部变量空间（根据 parser 记录的 local_vars_count）
            local_vars_count = proc_info.get('local_vars_count', 0)
            self.code.append(('INT', 0, local_vars_count))
            
            # 调用过程（注意：这里的 entry_addr 需是实际代码地址，此处为示例）
            self.code.append(('CAL', 0, entry_addr))
            
            # 返回指令
            self.code.append(('OPR', 0, 0))
        
        elif block[0] == 'begin':
            _, statements = block
            for stmt in statements:
                self.generate_block(stmt)
        
        elif block[0] == 'if':
            _, cond, stmt = block
            false_label = self.new_label()
            end_label = self.new_label()
            
            self.generate_condition(cond, false_label)
            self.generate_block(stmt)
            self.code.append(('JMP', 0, end_label))
            
            self.place_label(false_label)
            self.place_label(end_label)
        
        elif block[0] == 'while':
            _, cond, stmt = block
            start_label = self.new_label()
            false_label = self.new_label()
            
            self.place_label(start_label)
            self.generate_condition(cond, false_label)
            self.generate_block(stmt)
            self.code.append(('JMP', 0, start_label))
            
            self.place_label(false_label)
        
        elif block[0] == 'read':
            _, ident = block
            addr = self.symbol_table.get(ident)
            if addr is not None:
                self.code.append(('OPR', 0, 14))  # 读操作
                self.code.append(('STO', 0, addr))
            else:
                raise Exception(f"未定义的变量: {ident}")
        
        elif block[0] == 'write':
            _, expr = block
            self.generate_expression(expr)
            self.code.append(('OPR', 0, 15))  # 写操作
        
        elif block[0] == 'empty':
            pass

    def generate_expression(self, expr):
        """生成表达式代码"""
        if expr[0] == 'number':
            _, num = expr
            self.code.append(('LIT', 0, num))
        
        elif expr[0] == 'identifier':
            _, ident = expr
            value = self.symbol_table.get(ident)
            if value is None:
                raise Exception(f"未定义变量: {ident}")
            if isinstance(value, int):  # 变量
                self.code.append(('LOD', 0, value))
            else:  # 常量
                self.code.append(('LIT', 0, value))
        
        elif expr[0] == 'negate':
            _, operand = expr
            self.generate_expression(operand)
            self.code.append(('OPR', 0, 1))  # 取负
        
        elif expr[0] in ['PLUS', 'MINUS', 'MULTIPLY', 'DIVIDE']:
            op, left, right = expr
            self.generate_expression(left)
            self.generate_expression(right)
            
            if op == 'PLUS':
                self.code.append(('OPR', 0, 2))
            elif op == 'MINUS':
                self.code.append(('OPR', 0, 3))
            elif op == 'MULTIPLY':
                self.code.append(('OPR', 0, 4))
            elif op == 'DIVIDE':
                self.code.append(('OPR', 0, 5))
        elif expr[0] == 'identifier':
            _, ident = expr
            value = self.symbol_table.get(ident)
            if value is None:
                raise Exception(f"未定义的标识符: {ident}")
            
            # 区分变量和常量
            if ident in self.procedures:
                # 过程调用（虽然这里不应该出现）
                pass
            else:
                # 变量或常量
                if isinstance(value, int):  # 变量（存储的是地址）
                    self.code.append(('LOD', 0, value))
                else:  # 常量（存储的是值）
                    self.code.append(('LIT', 0, value))

    def generate_condition(self, cond, false_label):
        """生成条件代码"""
        if cond[0] == 'odd':
            _, expr = cond
            self.generate_expression(expr)
            self.code.append(('OPR', 0, 6))  # ODD操作
            self.code.append(('JPC', 0, false_label))
        else:
            op, left, right = cond
            self.generate_expression(left)
            self.generate_expression(right)
            
            # 生成比较操作
            if op == 'EQUAL':
                self.code.append(('OPR', 0, 8))
            elif op == 'NOT_EQUAL':
                self.code.append(('OPR', 0, 9))
            elif op == 'LESS':
                self.code.append(('OPR', 0, 10))
            elif op == 'GREATER_EQUAL':
                self.code.append(('OPR', 0, 11))
            elif op == 'GREATER':
                self.code.append(('OPR', 0, 12))
            elif op == 'LESS_EQUAL':
                self.code.append(('OPR', 0, 13))
            
            self.code.append(('JPC', 0, false_label))

    def place_label(self, label):
        """放置标签"""
        self.labels[label] = len(self.code)
