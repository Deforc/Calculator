#include <iostream>
#include <map>
#include <string>
#include <vector>
int main() {
    std::map<char, int> operatorMap;
    operatorMap['('] = { 4 };
    operatorMap[')'] = { 4 };
    operatorMap['+'] = { 1 };
    operatorMap['-'] = { 1 };
    operatorMap['*'] = { 2 };
    operatorMap['/'] = { 2 };
    std::vector<std::string> parsedExpression;
    std::string s = "58+28sin(90)-1745+cos(90)-2^4+5gcd10";
    std::string buffer = "";
    for (char c : s)
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
    for (int i = 0 ; i < parsedExpression.size(); i++)
    {
        std::cout << "\"" << parsedExpression[i] << "\"" << " ";
    }
}
