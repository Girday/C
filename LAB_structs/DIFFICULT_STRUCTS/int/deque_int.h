#pragma once

typedef struct {
    int* buf;
    int len;
    int max_len;
    int start;
} deque_int;

deque_int* dint_create(int max_len);
void dint_destroy(deque_int* dint);
int dint_is_empty(deque_int* dint);
int dint_push_back(deque_int* dint, int val);
int dint_push_front(deque_int* dint, int val);
int dint_pop_back(deque_int* dint);
int dint_pop_front(deque_int* dint);
