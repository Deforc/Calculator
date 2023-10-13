#include <cmath>

extern "C"  {
int arity = 1;
char funcDefinition[3] = "ln";
char funcName[14] = "external_func";
double external_func(double a) {
    return log(a);
}
}
