#include <stdio.h>
#include "functions.h"


int main() {

    int i = fact(5);
//  printf("%d\n", i) // Нет точки с запятой - синтаксическая ошибка
    printf("%d\n", i);

//  int E = i * "5"; // int умножить на char - ошибка типа данных

    int j = pow2(7);
    printf("%d\n", j);

    int k = div(-17, 3);
    printf("%d\n", k);

    int l = mod(50, -12);
    printf("%d\n", l);
    
}