#include <cmath>
#include <string>
extern "C"  {
int arity = 1;
char funcDefinition[4] = "sin";
char funcName[14] = "external_func";
double external_func(double a) {
    return sin(a);
}
}