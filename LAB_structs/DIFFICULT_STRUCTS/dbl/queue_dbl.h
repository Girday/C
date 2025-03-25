#pragma once

typedef struct {
    double* buf;
    int len;
    int max_len;
    int start;
} queue_dbl;

queue_dbl* qdbl_create(int max_len);
void qdbl_destroy(queue_dbl* qdbl);
int qdbl_is_empty(queue_dbl* qdbl);
int qdbl_push(queue_dbl* qdbl, double val);
double qdbl_pop(queue_dbl* qdbl);
int qdbl_shrink_if_needed(queue_dbl* qdbl);
