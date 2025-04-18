#include "stack_int.h"
#include <stdlib.h>
#include <stdio.h>

stack_int* sint_create(int max_len) {

    stack_int* res = malloc(sizeof(stack_int));

    if (res == NULL) {
        fprintf(stderr, "Creating stack of int is failed\n\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(int) * max_len);

    if (res -> buf == NULL) {

        fprintf(stderr, "Creating stack of int is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> max_len = max_len;

    return res;

}

void sint_destroy(stack_int* sint){
    free(sint -> buf);
    free(sint);
}

int sint_is_empty(stack_int* sint) {
    return sint -> len == 0;
}

int sint_pop(stack_int* sint) {
    
    if (sint_is_empty(sint)) {
        fprintf(stderr, "Stack of int is empty\n\n");
        exit(-1);
    }

    int elem = sint -> buf[sint -> len - 1];
    sint -> len--;

    return elem;

}

int sint_top(stack_int* sint) {
    int res = sint_pop(sint);
    sint_push(sint, res);

    return res;
}

static int grow(stack_int* sint) {

    int new_max_len = sint -> max_len * 2; // 2 - лютая константа с кайфом

    int* new_buf = realloc(sint -> buf, sizeof(int) * new_max_len);

    if (new_buf == NULL)
        return 0;
    
    sint -> buf = new_buf;
    sint -> max_len = new_max_len;

    return 1;

}

int sint_push(stack_int* sint, int val) {

    if (sint -> len == sint -> max_len)
        if (!grow(sint))
            return 0;

    sint -> buf[sint -> len] = val;
    sint -> len++;

    return 1;

}
