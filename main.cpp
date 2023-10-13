#include <iostream>
#include "MathParser.h"
#include "Calculator.h"

int main() {
   std::string expr = "";
   std::string pluginDir = "..\\plugins\\";
   MathParser mathParser = MathParser();
   Calculator calculator = Calculator(pluginDir);

   while (true) {
       std::getline(std::cin, expr);
       mathParser.parseExpression(expr);
       calculator.removeUnMinus(mathParser.getTokenizedExpression());
       calculator.checkIncorrectInput(mathParser.getTokenizedExpression());
       calculator.reversedPolishNotation(mathParser.getTokenizedExpression());
       std::cout << "Answer: " << calculator.solve() << std::endl;
       calculator.clearStacks();
       mathParser.clearStack();
   }

}
