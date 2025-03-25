#include <stdio.h>

int main() {
    int a = 0, b = 1, c;
    
    printf("%d\n", a);
    while (b < 1000) {
        printf("%d\n", b);
        c = b;
        b += a;
        a = c;
    }
}