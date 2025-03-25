#include "deque_int.h"
#include <stdio.h>
#include <stdlib.h>

deque_int* dint_create(int max_len) {

    deque_int* res = malloc(sizeof(deque_int));

    if (res == NULL) {
        fprintf(stderr, "Creating deque of int is failed\n\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(int) * max_len);

    if (res -> buf == NULL) {
        
        fprintf(stderr, "Creating deque of int is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;

}

void dint_destroy(deque_int* dint) {
    free(dint -> buf);
    free(dint);
}

int dint_is_empty(deque_int* dint) {
    return dint -> len == 0;    
}

int dint_pop_back(deque_int* dint) {

    if (dint -> len == 0) {
        fprintf(stderr, "Deque of int is empty\n\n");
        exit(-1);
    }

    int elem = dint -> buf[(dint -> start + dint -> len - 1) % dint -> max_len];
    dint -> len--;

    return elem;

}

int dint_pop_front(deque_int* dint) {

    if (dint -> len == 0) {
        fprintf(stderr, "Deque of int is empty\n\n");
        exit(-1);
    }

    int elem = dint -> buf[dint -> start];
    dint -> start = (dint -> start + 1) % dint -> max_len;
    dint -> len--;

    return elem;

}

static int grow(deque_int* dint) {

    int new_max_len = dint -> max_len * 2;

    int* new_buf = realloc(dint -> buf, sizeof(int) * new_max_len);

    if (new_buf == NULL)
        return 0;

    for (int i = dint -> max_len - 1; i >= dint -> start; i--)
        new_buf[new_max_len - dint -> max_len + i] = new_buf[i];

    dint -> start += new_max_len - dint -> max_len;
    dint -> buf = new_buf;
    dint -> max_len = new_max_len;
    
    return 1;

}

int dint_push_back(deque_int* dint, int val) {

    if (dint -> len == dint -> max_len)
        if (!grow(dint))
            return 0;
    
    dint -> buf[(dint -> start + dint -> len) % dint -> max_len] = val;
    dint -> len++;

    return 1;

}

int dint_push_front(deque_int* dint, int val) {

    if (dint -> len == dint -> max_len)
        if (!grow(dint))
            return 0;

    dint -> start = (dint -> start - 1 + dint -> max_len) % dint -> max_len;
    dint -> buf[dint -> start] = val;
    dint -> len++;

    return 1;

}
