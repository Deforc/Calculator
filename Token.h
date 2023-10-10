#ifndef CALCULATOR_CPP_TOKEN_H
#define CALCULATOR_CPP_TOKEN_H
#include <string>

enum precedence { NONE = 0, LOW = 1, UPPER_LOW = 2, MEDIUM = 3, HIGH = 4};

class Token {
public:
    Token(std::pair<int, std::string> token) { this->token = token; };
    std::string getValue() { return this->token.second; }
    int getPrecedence() { return this->token.first; }
private:
    std::pair<int, std::string> token;
};


#endif //CALCULATOR_CPP_TOKEN_H
