from lexer import Lexer
from parser import Parser
from code_generator import CodeGenerator
import sys

def main():
    if len(sys.argv) < 2:
        print("用法: python compiler.py <源文件>")
        return
    
    source_file = sys.argv[1]
    
    try:
        # 读取源代码
        with open(source_file, 'r', encoding='utf-8') as f:
            source_code = f.read()
        
        if not source_code.strip():
            print("错误: 源文件为空")
            return
        
        # 词法分析
        lexer = Lexer(source_code)
        tokens = lexer.tokenize()
        
        if not tokens:
            print("错误: 词法分析未生成有效token")
            return
        
        # 语法分析
        parser = Parser(tokens)
        ast = parser.parse()
        
        # 检查错误
        if parser.errors:
            print("编译错误:")
            for error in parser.errors:
                print(error)
            return
        
        # 代码生成
        code_gen = CodeGenerator(ast, parser.symbol_table, parser.procedures)
        p_code = code_gen.generate()
        
        # 输出生成的P-code
        print("\n生成的P-code:")
        for i, (op, l, a) in enumerate(p_code):
            print(f"{i:3}: {op} {l} {a}")
        
        
    except FileNotFoundError:
        print(f"错误: 文件 '{source_file}' 不存在")

if __name__ == "__main__":
    main()
