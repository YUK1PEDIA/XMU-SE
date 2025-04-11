#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cmath>

using namespace std;

// 检查字符串是否表示八进制整数，并转换值
bool checkOctalNumber(const string& inputStr, int &convertedValue) {
    // 八进制格式必须至少3个字符：0o开头
    if (inputStr.size() < 3 || inputStr[0] != '0' || (inputStr[1] != 'o' && inputStr[1] != 'O')) 
        return false;
    
    // 检查后续字符是否都是0-7的数字
    for (size_t index = 2; index < inputStr.size(); index++) {
        if (inputStr[index] < '0' || inputStr[index] > '7') 
            return false;
    }
    
    // 将八进制字符串转换为整数
    convertedValue = stoi(inputStr.substr(2), nullptr, 8);
    return true;
}

// 检查字符串是否表示十六进制浮点数，并转换值
bool verifyHexFloatValue(const string& inputStr, double &resultValue) {
    // 十六进制格式必须至少3个字符：0x开头
    if (inputStr.size() < 3 || inputStr[0] != '0' || (inputStr[1] != 'x' && inputStr[1] != 'X')) 
        return false;

    // 查找小数点位置
    size_t decimalPointPos = inputStr.find('.');
    bool containsDecimal = (decimalPointPos != string::npos);

    // 分离整数部分和小数部分
    string integerComponent = containsDecimal ? inputStr.substr(2, decimalPointPos - 2) : inputStr.substr(2);
    string fractionalComponent = containsDecimal ? inputStr.substr(decimalPointPos + 1) : "";

    // 不能同时为空
    if (integerComponent.empty() && fractionalComponent.empty()) 
        return false;

    // 转换整数部分
    double integerValue = integerComponent.empty() ? 0 : stoi(integerComponent, nullptr, 16);
    double fractionalValue = 0;
    
    // 转换小数部分
    if (!fractionalComponent.empty()) {
        for (size_t digitIndex = 0; digitIndex < fractionalComponent.size(); digitIndex++) {
            int digitValue = isdigit(fractionalComponent[digitIndex]) ? 
                           fractionalComponent[digitIndex] - '0' : 
                           tolower(fractionalComponent[digitIndex]) - 'a' + 10;
            fractionalValue += digitValue / pow(16, digitIndex + 1);
        }
    }

    resultValue = integerValue + fractionalValue;
    return true;
}

// 检查字符串是否表示十六进制整数，并转换值
bool validateHexadecimalInteger(const string& inputStr, int &outputValue) {
    // 十六进制格式必须至少3个字符：0x开头
    if (inputStr.size() < 3 || inputStr[0] != '0' || (inputStr[1] != 'x' && inputStr[1] != 'X')) 
        return false;
    
    // 检查后续字符是否都是有效的十六进制数字
    for (size_t charPos = 2; charPos < inputStr.size(); charPos++) {
        if (!isxdigit(inputStr[charPos])) 
            return false;
    }
    
    // 将十六进制字符串转换为整数
    outputValue = stoi(inputStr.substr(2), nullptr, 16);
    return true;
}

// 检查字符串是否表示八进制浮点数，并转换值
bool examineOctalFloat(const string& inputStr, double &decimalValue) {
    // 八进制格式必须至少3个字符：0o开头
    if (inputStr.size() < 3 || inputStr[0] != '0' || (inputStr[1] != 'o' && inputStr[1] != 'O')) 
        return false;
    
    // 必须包含小数点
    size_t pointPosition = inputStr.find('.');
    if (pointPosition == string::npos) 
        return false;
    
    // 检查所有字符是否都是有效的八进制数字或小数点
    for (size_t charIndex = 2; charIndex < inputStr.size(); charIndex++) {
        if (charIndex != pointPosition && (inputStr[charIndex] < '0' || inputStr[charIndex] > '7')) 
            return false;
    }
    
    // 分离整数部分和小数部分
    string wholeNumberPart = inputStr.substr(2, pointPosition - 2);
    string fractionalPart = inputStr.substr(pointPosition + 1);
    
    // 转换整数部分
    double wholeNumberValue = wholeNumberPart.empty() ? 0 : stoi(wholeNumberPart, nullptr, 8);
    double fractionalNumberValue = 0;
    
    // 转换小数部分
    if (!fractionalPart.empty()) {
        for (size_t digitPosition = 0; digitPosition < fractionalPart.size(); digitPosition++) {
            int digit = fractionalPart[digitPosition] - '0';
            fractionalNumberValue += digit / pow(8, digitPosition + 1);
        }
    }
    
    decimalValue = wholeNumberValue + fractionalNumberValue;
    return true;
}

// 检查字符串是否表示十进制浮点数，并转换值
bool isDecimalNumberWithPoint(const string& inputStr, double &numericValue) {
    // 必须包含小数点
    size_t decimalPosition = inputStr.find('.');
    if (decimalPosition == string::npos) 
        return false;  

    // 所有字符必须是数字或小数点
    for (char currentChar : inputStr) {
        if (!isdigit(currentChar) && currentChar != '.') 
            return false;
    }
    
    // 转换为双精度浮点数
    numericValue = stod(inputStr);
    return true;
}

// 词法分析函数，扫描输入字符串并识别各种token
void performLexicalAnalysis(const string& inputString) {
    size_t currentPosition = 0;
    while (currentPosition < inputString.size()) {
        // 跳过空白字符
        if (isspace(inputString[currentPosition])) {
            currentPosition++;
            continue;
        }

        cout << "Token type:";
        
        // 处理标识符或关键字
        if (isalpha(inputString[currentPosition])) {
            size_t startPosition = currentPosition;
            while (currentPosition < inputString.size() && (isalnum(inputString[currentPosition]) || inputString[currentPosition] == '_')) {
                currentPosition++;
            }
            string extractedToken = inputString.substr(startPosition, currentPosition - startPosition);
            
            // 检查是否为关键字
            if (extractedToken == "if" || extractedToken == "then" || extractedToken == "else" || 
                extractedToken == "while" || extractedToken == "do") {
                cout << "关键字: " << extractedToken << endl;
            } else {
                cout << "IDN " << extractedToken << endl;
            }
        } 
        // 处理数字常量
        else if (isdigit(inputString[currentPosition]) || inputString[currentPosition] == '.') {
            size_t tokenStart = currentPosition;
            bool isHexNumber = false, isOctalNumber = false;
            int integerResult = 0;
            double floatingResult = 0;

            // 检查是否为十六进制或八进制
            if (inputString[currentPosition] == '0' && currentPosition + 1 < inputString.size()) {
                if (inputString[currentPosition + 1] == 'x' || inputString[currentPosition + 1] == 'X') 
                    isHexNumber = true;
                else if (inputString[currentPosition + 1] == 'o' || inputString[currentPosition + 1] == 'O') 
                    isOctalNumber = true;
            }

            // 扫描整个数字token
            while (currentPosition < inputString.size() && 
                  (isdigit(inputString[currentPosition]) || isxdigit(inputString[currentPosition]) || 
                   inputString[currentPosition] == '.' || inputString[currentPosition] == 'x' || 
                   inputString[currentPosition] == 'X' || inputString[currentPosition] == 'o' || 
                   inputString[currentPosition] == 'O')) {
                currentPosition++;
            }

            string numberToken = inputString.substr(tokenStart, currentPosition - tokenStart);

            // 尝试匹配各种数字格式
            if (isOctalNumber && examineOctalFloat(numberToken, floatingResult)) {
                cout << "FLOAT8 " << floatingResult << endl;
            } else if (isHexNumber && validateHexadecimalInteger(numberToken, integerResult)) {
                cout << "INT16 " << integerResult << endl;
            } else if (isOctalNumber && checkOctalNumber(numberToken, integerResult)) {
                cout << "INT8 " << integerResult << endl;
            } else if (isHexNumber && verifyHexFloatValue(numberToken, floatingResult)) {
                cout << "FLOAT16 " << floatingResult << endl;
            } else if (isDecimalNumberWithPoint(numberToken, floatingResult)) {
                cout << "FLOAT10 " << floatingResult << endl;
            } else if (isdigit(numberToken[0])) {
                cout << "INT10 " << stoi(numberToken) << endl;
            } else {
                cout << "未知数值: " << numberToken << endl;
            }
        } 
        // 处理运算符和分隔符
        else {
            cout << "运算符/分隔符: " << inputString[currentPosition] << endl;
            currentPosition++;
        }
    }
}

int main() {
    // 设置控制台编码为UTF-8
    system("chcp 65001");
    
    string userInput;
    while (true) {
        getline(cin, userInput);
        if (userInput == "q") {
            break;
        }
        performLexicalAnalysis(userInput);
    }
    return 0;
}