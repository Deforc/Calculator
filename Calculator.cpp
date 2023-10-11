#include "Calculator.h"

Calculator::Calculator(std::string pluginDirectory) {
    this->pluginDirectory = pluginDirectory;
}

void Calculator::clearStacks() {
    while (!operatorStack.empty()) {
        operatorStack.pop();
    }
    while (!digitStack.empty()) {
        digitStack.pop();
    }
    while (!rpn.empty()) {
        rpn.pop_back();
    }
}

void Calculator::setOperators() {
    this->binaryFunctions.push_back({ [](double fst, double snd) { return fst + snd; }, "+" });
    this->binaryFunctions.push_back({ [](double fst, double snd) { return fst - snd; }, "-" });
    this->binaryFunctions.push_back({ [](double fst, double snd) { return fst * snd; }, "*" });
    this->binaryFunctions.push_back({ [](double fst, double snd) { return fst / snd; }, "/" });
}

UnaryFunction Calculator::checkUnary(Token token) {
    for (auto func : unaryFunctions) {
        if (func.getName() == token.getValue())
            return func;
    }
    throw std::runtime_error("Function isn`t found");

}

BinaryFunction Calculator::checkBinary(Token token) {
    for (auto func : binaryFunctions) {
        if (func.getName() == token.getValue())
            return func;
    }
    throw std::runtime_error("Function isn`t found");
}

void Calculator::reversedPolishNotation(std::vector<Token> tokenizedExpression) {
    for (auto token : tokenizedExpression) {
        switch (token.getDefinition()) {
            case NUMBER:
                rpn.push_back(token);
                break;
            case FUNCTION:
                operatorStack.push(token);
                break;
            case OPERATOR:
                while(!operatorStack.empty()
                        && (operatorStack.top().getDefinition() != LEFT_BRACKET
                        && operatorStack.top().getPrecedence() >= token.getPrecedence()))
                {
                    rpn.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
                break;
            case LEFT_BRACKET:
                operatorStack.push(token);
                break;
            case RIGHT_BRACKET:
                while (!operatorStack.empty()
                        && operatorStack.top().getDefinition() != LEFT_BRACKET) {
                    rpn.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                if (operatorStack.top().getDefinition() == LEFT_BRACKET)
                    operatorStack.pop();
                if (operatorStack.top().getDefinition() == FUNCTION) {
                    rpn.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                break;

        }

    }
    while (!operatorStack.empty()) {
        if(operatorStack.top().getDefinition() != LEFT_BRACKET)
            rpn.push_back(operatorStack.top());
        operatorStack.pop();
    }
}

double Calculator::solve() {
    UnaryFunction unaryFunc;
    BinaryFunction binaryFunc;
    for (auto token : rpn) {
        if(token.getDefinition() == NUMBER)
            digitStack.push(std::stod(token.getValue()));
        else if (token.getDefinition() == FUNCTION && !digitStack.empty()) {
            unaryFunc = checkUnary(token);
            unaryFunc.setArguments(digitStack.top());
            digitStack.pop();
            digitStack.push(unaryFunc.substitution());
        }
        else if (token.getDefinition() == OPERATOR && !digitStack.empty()) {
            binaryFunc = checkBinary(token);
            double argumentR = digitStack.top();
            digitStack.pop();
            if(!digitStack.empty())
            {
                double argumentL = digitStack.top();
                digitStack.pop();
                binaryFunc.setArguments(argumentL, argumentR);
            }
            digitStack.push(binaryFunc.substitution());

        } else
            throw std::runtime_error("Check order of operations!");

    }
    return digitStack.top();
}


