#ifndef CALCULATOR_CPP_CALCULATOR_H
#define CALCULATOR_CPP_CALCULATOR_H
#include "MathParser.h"
#include "Function.h"
#include <stack>
#include <exception>
#include <Windows.h>

class Calculator {
public:
    Calculator(std::string pluginDirectory);
    void reversedPolishNotation (std::vector<Token> tokenizedExpression);
    void clearStacks();
    double solve();
    void checkIncorrectInput(std::vector<Token> tokenizedExpression);
    void removeUnMinus(std::vector<Token> tokenizedExpression);


private:
    std::vector<Token> rpn;
    std::vector<UnaryFunction> unaryFunctions;
    std::vector<BinaryFunction> binaryFunctions;

    std::stack<Token> operatorStack;
    std::stack<double> digitStack;
    std::string pluginDirectory;

    UnaryFunction getUnary(Token token);
    BinaryFunction getBinary(Token token);
    UnaryFunction* checkUnary(Token token);
    BinaryFunction* checkBinary(Token token);

    void setOperators();
    void setFuncFromDll();
    void getFuncFromDLL(const std::string& filename);
};


#endif //CALCULATOR_CPP_CALCULATOR_H
