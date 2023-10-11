#ifndef CALCULATOR_CPP_TOKEN_H
#define CALCULATOR_CPP_TOKEN_H
#include <string>

enum tokenDefinition {LEFT_BRACKET = 1, RIGHT_BRACKET = 2, OPERATOR = 3, FUNCTION = 4, NUMBER = 5};

enum precedence { NONE = -1, LOW = 0, MEDIUM = 2, HIGH = 3};

class Token {
public:
    Token(std::pair<std::pair<int, int>, std::string> token) { this->token = token; };
    std::string getValue() { return this->token.second; }
    int getPrecedence() { return this->token.first.second; }
    int getDefinition() { return this->token.first.first; }
private:
    //first - definition, second - precedence, third - value
    std::pair<std::pair<int, int>, std::string> token;
};


#endif //CALCULATOR_CPP_TOKEN_H
