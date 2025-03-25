#include <stdio.h>
#include "functions.h" // Внутри functions.h происходит вызов main.c

//#include "non_exist.h" // Использование имени несуществующего файла
//#deFIne succes return 0 // Неправильно написанное ключевое слово препроцессора


int main() {

    int i = fact(5);
    printf("%d\n", i);

    int j = pow2(7);
    printf("%d\n", j);

    int k = div(-17, 3);
    printf("%d\n", k);

    int l = mod(50, -12);
    printf("%d\n", l);
    
}