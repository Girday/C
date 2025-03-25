#include <stdbool.h>
#include <math.h>


typedef double (*func)(double);

struct result {
    double root;
    int iters_count;
    bool success;
};

struct result dihotomia(func f, double left, double right) {
    
    struct result res = {.root=0, .iters_count=0, .success=false};
    
    if (f(left) * f(right) > 0)
        return res;

    int iters_count = 0;
    double delta = 0.00001;

    while (delta < right - left){
    
        double centre = (left + right) / 2;
    
        if (f(centre) * f(left) <= 0)
            right = centre;
        else
            left = centre;

        iters_count++;
    
    }

    res.root = (left + right) / 2;
    res.iters_count = iters_count;
    res.success = true;

    return res;

}


double df(func f, double x) {
    double dx = 0.000001;     
    return (f(x + dx) - f(x - dx)) / (2 * dx); 
}

double ddf(func f, double x) {
    double dx = 0.000001;
    return (f(x + dx) - 2 * f(x) + f(x - dx)) / (dx * dx); 
}


struct result iterations(func g, double x) {
    
    struct result res = {.root=0, .iters_count=0, .success=false};
    
    int iters_count = 0;
    double delta = 0.00001;

    while (!(fabs(g(x) - x) < delta)) {
        
        if (fabs(df(g, x)) < 1) {
            x = g(x);
        } 

        else {
            res.iters_count = iters_count;
            return res;
        }

        iters_count++;

    }

    res.success = true;
    res.root = x;
    res.iters_count = iters_count;

    return res;
}

struct result newton(func f, double x) {

    struct result res = {.root=0, .iters_count=0, .success=false};

    int iters_count = 0;
    double delta = 0.00001;

    while (!(fabs(f(x)) < delta)) {

        if (fabs(f(x) * ddf(f, x)) < (df(f, x) * df(f, x)))
            x = x - f(x) / df(f, x);
        else
            return res;

        iters_count++;

    }

    res.success = true;
    res.root = x;
    res.iters_count = iters_count;

    return res;
}


