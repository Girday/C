#include <stdio.h>

int ways(int a, int b);
void print_down(int n);
void print_up(int n);

// Прямая рекурсия
int ways(int a, int b) {
    if (a > b) {return 0;}
    else if (a == b) {return 1;}
    else {return ways(a + 1, b) + ways(a * 2, b);}
}


// Косвенная рекурсия

void print_down(int n) {
    if (n <= 0) {
        return;
    }
    printf("%d ", n);
    print_up(n - 1);
}

void print_up(int n) {
    if (n <= 0) {
        return;
    }
    printf("%d ", n);
    print_down(n - 1);
}

// Тело
int main() {

    int l, r;
    
    scanf("%d %d", &l, &r);

    int i = ways(l, r);

    print_down(i);
    
}

