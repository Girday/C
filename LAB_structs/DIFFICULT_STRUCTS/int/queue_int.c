#include "queue_int.h"
#include <stdio.h>
#include <stdlib.h>

queue_int* qint_create(int max_len) {

    queue_int* res = malloc(sizeof(queue_int));

    if (res == NULL) {
        fprintf(stderr, "Creating queue of int is failed\n\n");        
        return NULL;
    }

    res -> buf = malloc(sizeof(int) * max_len);

    if (res -> buf == NULL) {

        fprintf(stderr, "Creating queue of int is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;

}

void qint_destroy(queue_int* qint) {
    free(qint -> buf);
    free(qint);
}

int qint_is_empty(queue_int* qint) {
    return qint -> len == 0;
}

int qint_pop(queue_int* qint) {

    if (qint_is_empty(qint)) {
        fprintf(stderr, "Queue of int is empty\n\n");
        exit(-1);
    }

    int elem = qint -> buf[qint -> start];

    qint -> start = (qint -> start + 1) % qint -> max_len;
    qint -> len--;

    return elem;

}

static int grow(queue_int* qint) {

    int new_max_len = qint -> max_len * 2;

    int* new_buf = realloc(qint -> buf, sizeof(int) * new_max_len);

    if (new_buf == NULL)
        return 0;

    for (int i = qint -> max_len - 1; i >= qint -> start; i--)
        new_buf[new_max_len - qint -> max_len + i] = new_buf[i];

    qint -> start += new_max_len - qint -> max_len;
    qint -> buf = new_buf;
    qint -> max_len = new_max_len;
    
    return 1;

}

int qint_push(queue_int* qint, int val) {

    if (qint -> len == qint -> max_len)
        if (!grow(qint))
            return 0;

    qint -> buf[(qint -> start + qint -> len) % qint -> max_len] = val;
    qint -> len++;

    return 1;

}
