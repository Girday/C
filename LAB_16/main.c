#include <stdio.h>
#include "methods.h"

double f19(double x) {
    return x - (1 / (3 + sin(3.6 * x)));
} // [0, 0.85] | 0.2624

double g19(double x) {
    return 1 / (3 + sin(3.6 * x));
}


double f20(double x) {
    return 0.1 * x * x - x * log(x);
} // [1, 2] | 1.1183

double g20(double x) {
    return (x * x) / (log(x) * 10);
}

double g20_2(double x) {
    return exp(0.1 * x);
}

int main() {

    printf("#19: x - (1 / (3 + sin(3.6 * x)))\n");

    printf("Dichotomia:\n\t");
    
    struct result res19_dihotomia = dihotomia(f19, 0, 0.85); 

        if (res19_dihotomia.success) 
            printf("x = %.6lf, iterations = %d\n", res19_dihotomia.root, res19_dihotomia.iters_count);
        else 
            printf("Dichotomy failed.\n");


    printf("Iterations:\n\t");

    struct result res19_iterations = iterations(g19, 0.425);

        if (res19_iterations.success) 
            printf("x = %.6lf, iterations = %d\n", res19_iterations.root, res19_iterations.iters_count);
        else 
            printf("Iterations failed.\n");


    printf("Newton:\n\t");

    struct result res19_newton = newton(f19, 0.425);
    
        if (res19_newton.success) 
            printf("x = %.6lf, iterations = %d\n", res19_newton.root, res19_newton.iters_count);
        else 
            printf("Newton failed.\n");


        
    printf("\n#20: 0.1 * x ^ 2 - x * ln(x)\n");

    printf("Dichotomia:\n\t");
    
    struct result res20_dihotomia = dihotomia(f20, 1, 2); 
    
        if (res20_dihotomia.success) 
            printf("x = %.6lf, iterations = %d\n", res20_dihotomia.root, res20_dihotomia.iters_count);
        else 
            printf("Dichotomy failed.\n");


    printf("Iterations for g20:\n\t");
    
    struct result res20_iterations = iterations(g20, 1);

        if (res20_iterations.success) 
            printf("x = %.6lf, iterations = %d\n", res20_iterations.root, res20_iterations.iters_count);
        else 
            printf("Failed\n");
        
    printf("Iterations for g20_2:\n\t");
    
    struct result res20_2_iterations = iterations(g20_2, 1);

        if (res20_2_iterations.success) 
            printf("x = %.6lf, iterations = %d\n", res20_2_iterations.root, res20_2_iterations.iters_count);
        else 
            printf("Failed\n");


    printf("Newton:\n\t");

    struct result res20_newton = newton(f20, 1.5);

        if (res20_newton.success) 
            printf("x = %.6lf, iterations = %d\n", res20_newton.root, res20_newton.iters_count);
        else 
            printf("Newton failed.\n");

}
