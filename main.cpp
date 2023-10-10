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
    std::string s = "-(4)+(-58+28)-1745*4-24+510/1+2^4";
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

    std::cout << std::endl;
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
            //to_tokenize[i].erase("-");
        }
    }
}
