#include <stdio.h>

int power_of_ten(int n) {

    if (n == 0) {
        return 1;
    }

    return 10 * power_of_ten(n - 1);

}

int len(int n) {

    if (n > 0 && n < 10) {
        return 1;
    }

    if (n < 0 && n > -10) {
        return 1;
    }

    return 1 + len(n / 10);

}

int count_zeroes(int n) {

    if (n % 10 != 0 || n == 0) {
        return 0;
    }

    return count_zeroes(n / 10) + 1;

}

int main() {

    int number;

    while (scanf("%d", &number) != EOF) {

        int length = len(number);

        int zeroes = count_zeroes(number);

        int center = power_of_ten(length / 2);

        number = (number / center) * center + (number % center) / power_of_ten(zeroes);

        printf("%d\n", number);

    }
}
