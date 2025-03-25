#include "stack_dbl.h"
#include <stdlib.h>
#include <stdio.h>

stack_dbl* sdbl_create(int max_len) {

    stack_dbl* res = malloc(sizeof(stack_dbl));

    if (res == NULL) {
        fprintf(stderr, "Creating stack of double is failed\n\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(double) * max_len);

    if (res -> buf == NULL) {

        fprintf(stderr, "Creating stack of double is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> max_len = max_len;

    return res;

}

void sdbl_destroy(stack_dbl* sdbl) {
    free(sdbl -> buf);
    free(sdbl);
}

int sdbl_is_empty(stack_dbl* sdbl) {
    return sdbl -> len == 0;
}

double sdbl_pop(stack_dbl* sdbl) {
    
    if (sdbl_is_empty(sdbl)) {
        fprintf(stderr, "Stack of double is empty\n\n");
        exit(-1);
    }

    double elem = sdbl -> buf[sdbl -> len - 1];
    sdbl -> len--;

    return elem;

}

static int grow(stack_dbl* sdbl) {

    int new_max_len = sdbl -> max_len * 2; // 2 - лютая константа с кайфом

    double* new_buf = realloc(sdbl -> buf, sizeof(double) * new_max_len);

    if (new_buf == NULL)
        return 0;
    
    sdbl -> buf = new_buf;
    sdbl -> max_len = new_max_len;

    return 1;

}

int sdbl_push(stack_dbl* sdbl, double val) {

    if (sdbl -> len == sdbl -> max_len)
        if (!grow(sdbl))
            return 0;

    sdbl -> buf[sdbl -> len] = val;
    sdbl -> len++;

    return 1;

}

int sdbl_shrink_if_needed(stack_dbl* sdbl) {

    int new_max_len;

    if (sdbl -> len <= sdbl -> max_len / 4)
            new_max_len = sdbl -> max_len / 2;
    else
        return 0;

    double* new_buf = realloc(sdbl -> buf, sizeof(double) * new_max_len);
    
    sdbl -> buf = new_buf;
    sdbl -> max_len = new_max_len;

    return 1;

}

