#include <stdio.h>
#include "./dbl/queue_dbl.h"

int main() {
    queue_dbl* a = qdbl_create(2);

    qdbl_push(a, 1.1);
    qdbl_push(a, 1.2);
    qdbl_push(a, 1.3);
    qdbl_push(a, 1.4);
    qdbl_push(a, 1.5);
    qdbl_push(a, 2.1);
    qdbl_push(a, 2.2);
    qdbl_push(a, 2.3);
    qdbl_push(a, 2.4);
    qdbl_push(a, 2.5);
    qdbl_push(a, 3.1);
    qdbl_push(a, 3.2);
    
    printf("\nLen: %d\n", a -> len);

    printf("\nElems: ");
    for (int i = 0; i < 8; i++)
        printf("%.1f, ", qdbl_pop(a));

    printf("Len: %d\n", a -> len);

    printf("Max len: %d\n", a -> max_len);
    // qdbl_shrink_if_needed(a);

    printf("\nLen: %d", a -> len);
    printf("\nElems: ");

    for (int i = 0; i < 4; i++)
        printf("%.1f, ", qdbl_pop(a));
    
    printf("Max len: %d\n\n", a -> max_len);
}
