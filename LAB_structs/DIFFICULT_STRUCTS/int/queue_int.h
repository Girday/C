#pragma once

typedef struct {
    int* buf;
    int len;
    int max_len;
    int start;
} queue_int;

queue_int* qint_create(int max_len);
void qint_destroy(queue_int* qint);
int qint_is_empty(queue_int* qint);
int qint_push(queue_int* qint, int val);
int qint_pop(queue_int* qint);
