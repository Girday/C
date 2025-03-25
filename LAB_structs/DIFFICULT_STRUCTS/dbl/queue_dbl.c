#include "queue_dbl.h"
#include <stdio.h>
#include <stdlib.h>

queue_dbl* qdbl_create(int max_len) {

    queue_dbl* res = malloc(sizeof(queue_dbl));

    if (res == NULL) {
        fprintf(stderr, "Creating queue of double is failed\n\n");        
        return NULL;
    }

    res -> buf = malloc(sizeof(double) * max_len);

    if (res -> buf == NULL) {

        fprintf(stderr, "Creating queue of double is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;

}

void qdbl_destroy(queue_dbl* qdbl) {
    free(qdbl -> buf);
    free(qdbl);
}

int qdbl_is_empty(queue_dbl* qdbl) {
    return qdbl -> len == 0;
}

double qdbl_pop(queue_dbl* qdbl) {

    if (qdbl_is_empty(qdbl)) {
        fprintf(stderr, "Queue of double is empty\n\n");
        exit(-1);
    }

    double elem = qdbl -> buf[qdbl -> start];

    qdbl -> start = (qdbl -> start + 1) % qdbl -> max_len;
    qdbl -> len--;

    return elem;

}

static int grow(queue_dbl* qdbl) {

    int new_max_len = qdbl -> max_len * 2;

    double* new_buf = realloc(qdbl -> buf, sizeof(double) * new_max_len);

    if (new_buf == NULL)
        return 0;

    for (int i = qdbl -> max_len - 1; i >= qdbl -> start; i--)
        new_buf[new_max_len - qdbl -> max_len + i] = new_buf[i];

    qdbl -> start += new_max_len - qdbl -> max_len;
    qdbl -> buf = new_buf;
    qdbl -> max_len = new_max_len;
    
    return 1;

}

int qdbl_push(queue_dbl* qdbl, double val) {

    if (qdbl -> len == qdbl -> max_len)
        if (!grow(qdbl))
            return 0;

    qdbl -> buf[(qdbl -> start + qdbl -> len) % qdbl -> max_len] = val;
    qdbl -> len++;

    return 1;

}

int qdbl_shrink_if_needed(queue_dbl* qdbl) {

    int new_max_len;

    if (qdbl -> len <= qdbl -> max_len / 4)
            new_max_len = qdbl -> max_len / 2;
    else
        return 0;

    if (qdbl -> start + qdbl -> len >= new_max_len) {
        
        int cur_len = new_max_len - qdbl -> start - 1;

        for (cur_len; cur_len <= qdbl -> len; cur_len++)
            qdbl -> buf[(qdbl -> start + cur_len) % qdbl -> max_len] = qdbl -> buf[cur_len];
        
    }

    double* new_buf = realloc(qdbl -> buf, sizeof(double) * new_max_len);

    qdbl -> buf = new_buf;
    qdbl -> max_len = new_max_len;
    
    return 1;
}

