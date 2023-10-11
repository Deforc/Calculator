#ifndef CALCULATOR_CPP_FUNCTION_H
#define CALCULATOR_CPP_FUNCTION_H
#include <string>
#include <functional>

class Function {
public:
    Function() {}
    Function(std::string name)  { this->name = name; };
    std::string getName () { return this->name; }
    virtual double substitution() { return 0; }
protected:
    std::string name;
};

class UnaryFunction : public Function {
public:
    UnaryFunction() {}
    UnaryFunction(std::function<double(double)> func, std::string name) : Function(name) { this->func = func; }
    void setArguments(double argument) { this->argument = argument; }
    double substitution() override { return func(argument); }
private:
    std::function<double(double)> func;
    double argument;
};

class BinaryFunction : public Function {
public:
    BinaryFunction() {}
    BinaryFunction(std::function<double(double, double)> func, std::string name) : Function(name) { this->func = func; }
    void setArguments(double argumentLeft, double argumentRight) { this->argumentLeft = argumentLeft; this->argumentRight = argumentRight; }
    double substitution() override { return func(argumentLeft, argumentRight); }
private:
    std::function<double(double, double)> func;
    double argumentLeft, argumentRight;
};



#endif //CALCULATOR_CPP_FUNCTION_H
