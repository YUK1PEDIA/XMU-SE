#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <cstdlib>

using namespace std;

// 全局变量和函数声明
extern string yytext;
extern int yyleng;
extern int yylex();
extern void yyerror(const char* s);

// 词法单元类型
enum TokenType {
    TOK_ID, TOK_INT8, TOK_INT10, TOK_INT16, TOK_IF, TOK_THEN, TOK_ELSE, 
    TOK_WHILE, TOK_DO, TOK_ASSIGN, TOK_SEMICOLON, TOK_LPAREN, TOK_RPAREN, 
    TOK_PLUS, TOK_MINUS, TOK_MULTIPLY, TOK_DIVIDE, TOK_GREATER, TOK_LESS, 
    TOK_EQUAL, TOK_EOF
};

// 三地址码指令结构
struct Instruction {
    string op;
    string arg1;
    string arg2;
    string result;
    
    Instruction(string o, string a1, string a2, string res) 
        : op(o), arg1(a1), arg2(a2), result(res) {}
    
    string toString() const {
        if (op == "label")
            return result + ":";
        else if (op == "goto")
            return "goto " + result;
        else if (op.find("if") == 0)
            return op + " " + arg1 + " " + arg2 + " goto " + result;
        else
            return result + " := " + arg1 + " " + op + " " + arg2;
    }
};

// 四元式表
vector<Instruction> quadTable;

// 临时变量计数器
int tempCount = 0;

// 标签计数器
int labelCount = 0;

// 生成新的临时变量
string newtemp() {
    return "t" + to_string(++tempCount);
}

// 生成新的标签
string newlabel() {
    return "L" + to_string(++labelCount);
}

// 生成三地址码指令
void gen(string op, string arg1, string arg2, string result) {
    quadTable.push_back(Instruction(op, arg1, arg2, result));
}

// 符号表项
struct Symbol {
    string name;
    string type;
    string value;
    
    Symbol(string n, string t, string v) : name(n), type(t), value(v) {}
};

// 符号表
map<string, Symbol> symbolTable;

// 当前词法单元
int currentToken;

// 向前看一个词法单元
void advance() {
    currentToken = yylex();
}

// 匹配期望的词法单元
void match(int token) {
    if (currentToken == token)
        advance();
    else {
        stringstream ss;
        ss << "语法错误: 期望 " << token << ", 但得到 " << currentToken;
        yyerror(ss.str().c_str());
    }
}

// 表达式结果结构
struct Expr {
    string place;  // 存储表达式结果的变量
    string code;   // 生成的代码
    
    Expr(string p, string c) : place(p), code(c) {}
};

// 条件表达式结果结构
struct Cond {
    string code;   // 生成的代码
    string trueLabel;  // 条件为真时跳转的标签
    string falseLabel; // 条件为假时跳转的标签
    
    Cond(string c, string t, string f) : code(c), trueLabel(t), falseLabel(f) {}
};

// 语句结果结构
struct Stmt {
    string code;   // 生成的代码
    string nextLabel;  // 语句执行后的下一个标签
    
    Stmt(string c, string n) : code(c), nextLabel(n) {}
};

// 函数前置声明
Stmt S();
Cond C();
Expr E();
Expr T();
Expr F();

// 词法分析器实现（简化版）
string yytext;
int yyleng;
string testInput = "while (a3+15)>0xa do if x2 == 07 then while y<z do y = x * y / z;";
size_t inputPos = 0;

int yylex() {
    while (inputPos < testInput.length() && isspace(testInput[inputPos]))
        inputPos++;
    
    if (inputPos >= testInput.length())
        return TOK_EOF;
    
    char c = testInput[inputPos];
    
    // 识别标识符
    if (isalpha(c) || c == '_') {
        size_t start = inputPos;
        while (inputPos < testInput.length() && (isalnum(testInput[inputPos]) || testInput[inputPos] == '_'))
            inputPos++;
        
        yytext = testInput.substr(start, inputPos - start);
        yyleng = yytext.length();
        
        if (yytext == "if") return TOK_IF;
        if (yytext == "then") return TOK_THEN;
        if (yytext == "else") return TOK_ELSE;
        if (yytext == "while") return TOK_WHILE;
        if (yytext == "do") return TOK_DO;
        
        return TOK_ID;
    }
    
    // 识别数字
    if (isdigit(c)) {
        size_t start = inputPos;
        
        // 十进制数
        if (c != '0') {
            while (inputPos < testInput.length() && isdigit(testInput[inputPos]))
                inputPos++;
            yytext = testInput.substr(start, inputPos - start);
            yyleng = yytext.length();
            return TOK_INT10;
        }
        
        // 0开头的数
        inputPos++;
        if (inputPos < testInput.length()) {
            // 八进制
            if (isdigit(testInput[inputPos]) && testInput[inputPos] >= '0' && testInput[inputPos] <= '7') {
                while (inputPos < testInput.length() && isdigit(testInput[inputPos]) && testInput[inputPos] <= '7')
                    inputPos++;
                yytext = testInput.substr(start, inputPos - start);
                yyleng = yytext.length();
                return TOK_INT8;
            }
            // 十六进制 - 修改后的逻辑
            else if (testInput[inputPos] == 'x' || testInput[inputPos] == 'X') {
                inputPos++;
                size_t hexStart = inputPos;
                while (inputPos < testInput.length() && 
                      (isdigit(testInput[inputPos]) || 
                       (testInput[inputPos] >= 'a' && testInput[inputPos] <= 'f') || 
                       (testInput[inputPos] >= 'A' && testInput[inputPos] <= 'F')))
                    inputPos++;
                
                // 如果没有有效的十六进制数字，报错
                if (inputPos == hexStart) {
                    yyerror("词法错误: 无效的十六进制数");
                    return TOK_EOF;
                }
                
                yytext = testInput.substr(start, inputPos - start);
                yyleng = yytext.length();
                return TOK_INT16;
            }
        }
        
        // 单独的0
        yytext = "0";
        yyleng = 1;
        return TOK_INT10;
    }
    
    // 识别符号
    switch (c) {
        case '=':
            inputPos++;
            // 修复：正确处理赋值和相等运算符
            if (inputPos < testInput.length() && testInput[inputPos] == '=') {
                inputPos++;
                yytext = "==";
                yyleng = 2;
                return TOK_EQUAL;
            }
            yytext = "=";
            yyleng = 1;
            return TOK_ASSIGN;
        case ';':
            inputPos++;
            yytext = ";";
            yyleng = 1;
            return TOK_SEMICOLON;
        case '(':
            inputPos++;
            yytext = "(";
            yyleng = 1;
            return TOK_LPAREN;
        case ')':
            inputPos++;
            yytext = ")";
            yyleng = 1;
            return TOK_RPAREN;
        case '+':
            inputPos++;
            yytext = "+";
            yyleng = 1;
            return TOK_PLUS;
        case '-':
            inputPos++;
            yytext = "-";
            yyleng = 1;
            return TOK_MINUS;
        case '*':
            inputPos++;
            yytext = "*";
            yyleng = 1;
            return TOK_MULTIPLY;
        case '/':
            inputPos++;
            yytext = "/";
            yyleng = 1;
            return TOK_DIVIDE;
        case '>':
            inputPos++;
            yytext = ">";
            yyleng = 1;
            return TOK_GREATER;
        case '<':
            inputPos++;
            yytext = "<";
            yyleng = 1;
            return TOK_LESS;
        default:
            yyerror("词法错误: 不识别的字符");
            return TOK_EOF;
    }
}

// 语句处理函数
Stmt S() {
    Stmt result("", "");
    
    switch (currentToken) {
        case TOK_ID: {
            string id = yytext;
            advance();
            match(TOK_ASSIGN);
            Expr e = E();
            match(TOK_SEMICOLON);
            gen(":=", e.place, "", id);
            result.code = e.code;
            break;
        }
        
        case TOK_IF: {
            advance();
            Cond cond = C();
            match(TOK_THEN);
            Stmt s1 = S();
            
            if (currentToken == TOK_ELSE) {
                advance();
                Stmt s2 = S();
                
                string nextLabel = newlabel();
                gen("label", "", "", cond.trueLabel);
                gen("goto", "", "", s1.nextLabel);
                gen("label", "", "", cond.falseLabel);
                gen("goto", "", "", s2.nextLabel);
                gen("label", "", "", nextLabel);
                
                result.code = cond.code + s1.code + s2.code;
                result.nextLabel = nextLabel;
            } else {
                gen("label", "", "", cond.trueLabel);
                gen("goto", "", "", s1.nextLabel);
                gen("label", "", "", cond.falseLabel);
                
                result.code = cond.code + s1.code;
                result.nextLabel = cond.falseLabel;
            }
            break;
        }
        
        case TOK_WHILE: {
            string beginLabel = newlabel();
            string trueLabel = newlabel();
            string falseLabel = newlabel();
            
            advance();
            gen("label", "", "", beginLabel);
            Cond cond = C();
            match(TOK_DO);
            Stmt s1 = S();
            
            gen("label", "", "", trueLabel);
            gen("goto", "", "", beginLabel);
            gen("label", "", "", falseLabel);
            
            result.code = beginLabel + ": " + cond.code + s1.code;
            result.nextLabel = falseLabel;
            break;
        }
        
        default:
            yyerror("语法错误: 不期望的符号");
            break;
    }
    
    return result;
}

// 条件表达式处理函数 - 增强错误处理
Cond C() {
    Expr e1 = E();
    string op;
    
    // 记录比较运算符的词法单元类型，用于错误处理
    int comparisonOpToken = -1;
    
    switch (currentToken) {
        case TOK_GREATER:
            op = ">";
            comparisonOpToken = TOK_GREATER;
            advance();
            break;
        case TOK_LESS:
            op = "<";
            comparisonOpToken = TOK_LESS;
            advance();
            break;
        case TOK_EQUAL:
            op = "==";
            comparisonOpToken = TOK_EQUAL;
            advance();
            break;
        default:
            yyerror("语法错误: 期望比较运算符");
            // 添加默认返回值以避免未定义行为
            return Cond("", newlabel(), newlabel());
    }
    
    // 确保比较运算符后有右操作数
    if (currentToken == TOK_EOF) {
        yyerror("语法错误: 条件表达式不完整，缺少右操作数");
        // 添加默认返回值以避免未定义行为
        return Cond("", newlabel(), newlabel());
    }
    
    Expr e2 = E();
    string trueLabel = newlabel();
    string falseLabel = newlabel();
    
    gen("if", e1.place, op + " " + e2.place, trueLabel);
    gen("goto", "", "", falseLabel);
    
    return Cond(e1.code + e2.code, trueLabel, falseLabel);
}

// 表达式处理函数
Expr E() {
    Expr e1 = T();
    
    while (currentToken == TOK_PLUS || currentToken == TOK_MINUS) {
        string op = (currentToken == TOK_PLUS) ? "+" : "-";
        advance();
        Expr t = T();
        string temp = newtemp();
        gen(op, e1.place, t.place, temp);
        e1 = Expr(temp, e1.code + t.code);
    }
    
    return e1;
}

// 项处理函数
Expr T() {
    Expr t1 = F();
    
    while (currentToken == TOK_MULTIPLY || currentToken == TOK_DIVIDE) {
        string op = (currentToken == TOK_MULTIPLY) ? "*" : "/";
        advance();
        Expr f = F();
        string temp = newtemp();
        gen(op, t1.place, f.place, temp);
        t1 = Expr(temp, t1.code + f.code);
    }
    
    return t1;
}

// 因子处理函数
Expr F() {
    Expr result("", "");
    
    switch (currentToken) {
        case TOK_ID:
            result = Expr(yytext, "");
            advance();
            break;
        case TOK_INT8:
        case TOK_INT10:
        case TOK_INT16: {
            string value = yytext;
            if (currentToken == TOK_INT8) {
                // 八进制转十进制
                value = to_string(stoi(yytext, nullptr, 8));
            } else if (currentToken == TOK_INT16) {
                // 十六进制转十进制
                value = to_string(stoi(yytext, nullptr, 16));
            }
            result = Expr(value, "");
            advance();
            break;
        }
        case TOK_LPAREN:
            advance();
            result = E();
            match(TOK_RPAREN);
            break;
        default:
            yyerror("语法错误: 不期望的符号");
            break;
    }
    
    return result;
}

// 主函数
int main() {
    cout << "测试用例: " << testInput << endl;
    
    // 初始化词法分析器
    advance(); // 读取第一个词法单元
    
    // 处理多个语句
    while (currentToken != TOK_EOF) {
        Stmt stmt = S();
    }
    
    // 输出三地址代码
    cout << "\n生成的三地址代码:" << endl;
    for (const auto& instr : quadTable) {
        cout << instr.toString() << endl;
    }
    
    return 0;
}

// 错误处理函数
void yyerror(const char* s) {
    cerr << "错误: " << s << endl;
    exit(1);
}    