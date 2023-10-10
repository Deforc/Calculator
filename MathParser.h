#ifndef CALCULATOR_CPP_MATHPARSER_H
#define CALCULATOR_CPP_MATHPARSER_H
#include <iostream>
#include <vector>
#include <map>
#include "Token.h"

class MathParser {
public:
    MathParser();
    void parseExpression(std::string& expr);
    void clearStack();
    void removeSpaces(std::string& expr);
    // std::vector<Token> getParsedExpression() { return this->parsedExpression; }    void clearStack();
private:
    std::map <char, int> operatorMap;
    std::vector<std::string> parsedExpression;
};
#endif //CALCULATOR_CPP_MATHPARSER_H
