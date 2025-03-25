#include <stdio.h>

int main() {

    int mat[7][7];
    int dir[4] = {0, -1, 0, 1};

    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    int l = n, p = 0;
    
    int i = -1, j = n - 1;

    while (l) {

        for (int k = 0; k < l; k++) {
            j += dir[p % 4];
            i += dir[(p + 3) % 4];
            printf("%d ", mat[i][j]);
        }

        p++;
        l -= p % 2;

    }

    printf("\n");
    
}
