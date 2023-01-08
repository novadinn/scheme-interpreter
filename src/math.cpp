#include "math.h"

#include <math.h>

double absolute(double v) {
    return abs(v);
}

double expt(double a, double b) {
    return pow(a, b);
}

double mod(double a, double b) {
    return fmodf(a, b);
}

double quot(double a, double b) {
    return a / b;
}

double rem(double a, double b) {
    return mod(a, b);
}

bool int_p(double v) {
    double ab = abs(v);
    
    return ab == floor(ab);
}
