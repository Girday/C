#include <math.h>
#include <stdbool.h>

typedef double (*func)(double);

struct result {
    double root;
    int iters_count;
    bool success;
};

struct result dihotomia(func f, double left, double right);
struct result iterations(func g, double x);
struct result newton(func f, double x);
