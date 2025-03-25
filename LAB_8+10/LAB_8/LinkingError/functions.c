// int twice = 10; // Первое определение
 
void should_be(double x) {
    int t = 1 + 2;
} // Несовпадение сигнатур функций

int fact(int x) {
    if (x == 0) {return 1;}
    else {return x * fact(x - 1);}
}

int pow2(int x) {
    return x * x;
}

int div(int a, int b) {
    if ((a > 0 && b > 0) || (a < 0 && b < 0)) {
        return a / b;
    }

    if ((a > 0 && b < 0) || (a < 0 && b > 0)) {
        if (a % b == 0) {
            return a / b;
        } else {
            return a / b - 1;
        }
    }

    return 0;
}


int mod(int a, int b) {
    return a - b * div(a, b);
}