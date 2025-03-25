#pragma once

typedef struct {
    double* buf;
    int len;
    int max_len;
    int start;
} deque_dbl;

deque_dbl* ddbl_create(int max_len);
void ddbl_destroy(deque_dbl* ddbl);
int ddbl_is_empty(deque_dbl* ddbl);
int ddbl_push_back(deque_dbl* ddbl, double val);
int ddbl_push_front(deque_dbl* ddbl, double val);
double ddbl_pop_back(deque_dbl* ddbl);
double ddbl_pop_front(deque_dbl* ddbl);
int ddbl_shrink_if_needed(deque_dbl* ddbl);
