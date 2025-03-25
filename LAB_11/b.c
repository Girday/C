#include <stdio.h>

int main() {
    int a;


    do {
        printf("%d\n", a);
    }
    while ((a = getchar()) != EOF);
}
