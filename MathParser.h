#ifndef CALCULATOR_CPP_MATHPARSER_H
#define CALCULATOR_CPP_MATHPARSER_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Token.h"

class MathParser {
public:
    MathParser();
    void parseExpression(std::string& expr);
    void clearStack();
    void removeSpaces(std::string& expr);
    std::vector<Token> getTokenizedExpression() { return this->tokenizedExpression; }
private:
    std::map <std::string , std::pair<int, int>> operatorMap;
    std::vector<std::string> parsedExpression;
    std::vector<Token> tokenizedExpression;
};
#endif //CALCULATOR_CPP_MATHPARSER_H
