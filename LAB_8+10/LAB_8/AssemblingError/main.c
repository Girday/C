#include <stdio.h>
#include "functions.h"


int main() {

//  asm("move eax, 0"); // Несуществующая инструкция. Правильно -- asm("movl $0, %eax");
    
//  asm("movl $0 %eax"); // Нет запятой - недопустимое количество операндов

    int i = fact(5);
    printf("%d\n", i);

    int j = pow2(7);
    printf("%d\n", j);

    int k = div(-17, 3);
    printf("%d\n", k);

    int l = mod(50, -12);
    printf("%d\n", l);
    
}