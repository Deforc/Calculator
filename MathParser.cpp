#include "MathParser.h"
#include <algorithm>
MathParser::MathParser() {
    this->operatorMap['('] = { HIGH };
    this->operatorMap[')'] = { HIGH };
    this->operatorMap['+'] = { LOW };
    this->operatorMap['-'] = { LOW };
    this->operatorMap['*'] = { UPPER_LOW };
    this->operatorMap['/'] = { UPPER_LOW };
}

void MathParser::clearStack() {
    while (!parsedExpression.empty())
        parsedExpression.pop_back();
}
void MathParser::removeSpaces(std::string& expr) {
    expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());
}

void MathParser::parseExpression(std::string& expr) {

    //-----------------------Remove spaces-------------------------
    removeSpaces(expr);
    //-----------------------Remove spaces-------------------------

    //-----------------------Bracket checking----------------------
    int bracketCounter = 0;
    for(char c : expr) {
        if(c == '(') bracketCounter++;
        if(c == ')') bracketCounter--;
        if(bracketCounter < 0) throw std::invalid_argument ("Incorrect bracket input");
    }
    if(bracketCounter != 0) throw std::invalid_argument ("Incorrect bracket input");
    //-----------------------Bracket checking----------------------

    //-----------------------Parsing expression--------------------
    std::string buffer = "";
    for (char c : expr)
    {
        if(isdigit(c))
        {
            if(!buffer.empty() && !isdigit(buffer[0])) {
                parsedExpression.push_back(buffer);
                buffer.clear();
            }
            buffer.push_back(c);
        }

        else if(operatorMap.find(c)->first == c) {
            if(!buffer.empty()) {
                parsedExpression.push_back(buffer);
                buffer.clear();
            }
            buffer.push_back(c);
            parsedExpression.push_back(buffer);
            buffer.clear();
        } else {
            if(isdigit(*(buffer.end()-1))) {

                parsedExpression.push_back(buffer);
                buffer.clear();
            }
            buffer.push_back(c);

        }

    }
    if(!buffer.empty())
        parsedExpression.push_back(buffer);
    //-----------------------Parsing expression--------------------
}