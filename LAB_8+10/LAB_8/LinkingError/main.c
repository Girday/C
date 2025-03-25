#include <stdio.h>
#include "functions.h"

// void should_be(int x); // Объявление и реализация функции имеют разные сигнатуры

// int twice = 20; // Дважды определённая переменная => ошибка линковки

// void no(); // Неопределенный символ из-за отсутствия реализации функции

int main() {

//  no(); // Функция объявлена, но нигде не использована

    int i = fact(5);
    printf("%d\n", i);

    int j = pow2(7);
    printf("%d\n", j);

    int k = div(-17, 3);
    printf("%d\n", k);

    int l = mod(50, -12);
    printf("%d\n", l);
    
}