#include "MathParser.h"
#include <algorithm>
MathParser::MathParser() {
    this->operatorMap["("] = { LEFT_BRACKET, HIGH };
    this->operatorMap[")"] = { RIGHT_BRACKET, HIGH };
    this->operatorMap["+"] = { OPERATOR, LOW };
    this->operatorMap["-"] = { OPERATOR, LOW };
    this->operatorMap["*"] = { OPERATOR, UPPER_LOW };
    this->operatorMap["/"] = { OPERATOR, UPPER_LOW };
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
    std::string castingString;
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

        else if(operatorMap.find(castingString = c)->first == castingString) {
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
    buffer.clear();
    //-----------------------Parsing expression--------------------

    //-------------------Replacing unary minus---------------------
    for (int i = 0; i < parsedExpression.size(); i++) {
        if (parsedExpression[0].find("-") == 0) {
            parsedExpression[0 + 1].insert(0, "-");
            parsedExpression[0].replace(0, 1, "0");
            parsedExpression.insert(parsedExpression.begin() + 1, "+");
            i+=2;
        }
        else if ((parsedExpression[i].find("-") == 0 && parsedExpression[i-1] == "(")) {
            parsedExpression[i + 1].insert(0, "-");
            parsedExpression.insert(parsedExpression.begin() + i + 1, "+");
            parsedExpression[i].replace(0, 1, "0");
            i+=2;
        }
    }
    //-------------------Replacing unary minus---------------------

    //----------Setting definition, precedence and value-----------
    for (auto elem : parsedExpression) {
        if (operatorMap.find(elem) != operatorMap.end())
            tokenizedExpression.push_back({{operatorMap[elem], elem}});
        else {
            try { double number = stod(elem); tokenizedExpression.push_back({{{NUMBER, NONE}, elem}}); }
            catch (const std::invalid_argument& e) { tokenizedExpression.push_back({ { {FUNCTION, MEDIUM}, elem} }); }
        }
    }
    //----------Setting definition, precedence and value-----------

}