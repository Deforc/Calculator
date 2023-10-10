#ifndef CALCULATOR_CPP_TOKEN_H
#define CALCULATOR_CPP_TOKEN_H
#include <string>

enum tokenDefinition {LEFT_BRACKET = 1, RIGHT_BRACKET = 2, OPERATOR = 3, FUNCTION = 4, NUMBER = 5};

enum precedence { NONE = 0, LOW = 1, UPPER_LOW = 2, MEDIUM = 3, HIGH = 4};

class Token {
public:
    Token(std::pair<std::pair<int, int>, std::string> token) { this->token = token; };
    std::string getValue() { return this->token.second; }
    int getPrecedence() { return this->token.first.second; }
private:
    //first - definition, second - precedence, third - value
    std::pair<std::pair<int, int>, std::string> token;
};


#endif //CALCULATOR_CPP_TOKEN_H
