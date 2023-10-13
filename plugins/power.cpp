#include <cmath>

extern "C"  {
int arity = 2;
char funcDefinition[2] = "^";
char funcName[14] = "external_func";
double external_func(double a, double b) {
    return pow(a, b);
}
}
