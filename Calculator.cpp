#include "Calculator.h"

Calculator::Calculator(std::string pluginDirectory) {
    this->pluginDirectory = pluginDirectory;
    setOperators();
    setFuncFromDll();
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

void Calculator::getFuncFromDLL(const std::string &filename) {
    HMODULE hm = LoadLibraryA((pluginDirectory + filename).c_str());
    if (hm == nullptr) {
        throw std::runtime_error("dll not found");
    }

    std::string funcDefinition (reinterpret_cast<char *>(GetProcAddress(hm, "funcDefinition")));
    std::string funcName (reinterpret_cast<char *>(GetProcAddress(hm, "funcName")));
    int* arity = reinterpret_cast<int *>(GetProcAddress(hm, "arity"));

    if(*arity == 1)
    {
        std::function<double(double)> importFunc = reinterpret_cast<double(*)(double)>(GetProcAddress(hm, funcName.c_str()));
        if (importFunc == nullptr) {
            throw std::runtime_error("failed to load function");
        }
        this->unaryFunctions.push_back({ importFunc, funcDefinition });
    } else if(*arity == 2)
    {
        std::function<double(double,double )> importFunc = reinterpret_cast<double(*)(double, double )>(GetProcAddress(hm, funcName.c_str()));
        if (importFunc == nullptr) {
            throw std::runtime_error("failed to load function");
        }
        this->binaryFunctions.push_back({ importFunc, funcDefinition });
    }


}

void Calculator::setFuncFromDll() {
    WIN32_FIND_DATAA wfd;
    HANDLE const hFind = FindFirstFileA((this->pluginDirectory + std::string("*.dll")).c_str(), &wfd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string dllFileName(wfd.cFileName);
            getFuncFromDLL(dllFileName);
        } while (NULL != FindNextFileA(hFind, &wfd));
        FindClose(hFind);
    }
    else {
        throw std::runtime_error("path not found");
    }
}

void Calculator::setOperators() {
    this->binaryFunctions.push_back({ [](double fst, double snd) { return fst + snd; }, "+" });
    this->binaryFunctions.push_back({ [](double fst, double snd) { return fst - snd; }, "-" });
    this->binaryFunctions.push_back({ [](double fst, double snd) { return fst * snd; }, "*" });
    this->binaryFunctions.push_back({ [](double fst, double snd) { return fst / snd; }, "/" });
}

UnaryFunction Calculator::getUnary(Token token) {
    if(checkUnary(token) != nullptr)
        return *checkUnary(token);

    throw std::runtime_error("Function isn`t found");

}

UnaryFunction *Calculator::checkUnary(Token token) {
    for (auto &func : unaryFunctions) {
        if (func.getName() == token.getValue())
            return &func;
    }
    return nullptr;
}

BinaryFunction Calculator::getBinary(Token token) {
    if(checkBinary(token) != nullptr)
        return *checkBinary(token);

    throw std::runtime_error("Function isn`t found");
}

BinaryFunction *Calculator::checkBinary(Token token) {
    for (auto &func : binaryFunctions) {
        if (func.getName() == token.getValue())
            return &func;
    }
    return nullptr;
}

void Calculator::checkIncorrectInput(std::vector<Token> tokenizedExpression) {
    if (checkBinary(tokenizedExpression[0]) != nullptr)
        throw std::runtime_error ("Incorrect input: binary operator can`t be first");

    if(checkBinary(tokenizedExpression.back()) != nullptr || checkUnary(tokenizedExpression.back()) != nullptr)
        throw std::runtime_error ("incorrect input");

    for (int i = 0 ; i < tokenizedExpression.size(); i++)
    {
        if(checkBinary(tokenizedExpression[i]) != nullptr && checkBinary(tokenizedExpression[i+1]) != nullptr)
            throw std::runtime_error("Incorrect input: you can`t use double binary operator");
        if(checkUnary(tokenizedExpression[i]) != nullptr && checkBinary(tokenizedExpression[i+1]) != nullptr)
            throw std::runtime_error("Incorrect input: you can`t use unary and then binary operators");
        if(tokenizedExpression[i].getDefinition() == NUMBER && checkUnary(tokenizedExpression[i]) != nullptr)
            throw std::runtime_error("Incorrect input: you can`t use number and then unary operator");
    }

}

void Calculator::removeUnMinus(std::vector<Token> tokenizedExpression) {
    for (int i = 0; i < tokenizedExpression.size(); i++) {
        if ((tokenizedExpression[i].getValue() == "-" && tokenizedExpression[i-1].getValue() == "(" /*digit check*/)) {
            tokenizedExpression[i + 1].setValue({{NUMBER, NONE}, "-" + tokenizedExpression[1].getValue()});
            tokenizedExpression.erase(tokenizedExpression.begin()+i);
            i++;
        }
    }
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
            unaryFunc = getUnary(token);
            unaryFunc.setArguments(digitStack.top());
            digitStack.pop();
            digitStack.push(unaryFunc.substitution());
        }
        else if (token.getDefinition() == OPERATOR && !digitStack.empty()) {
            binaryFunc = getBinary(token);
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





