#pragma once

typedef struct {
    double* buf;
    int len;
    int max_len;
} stack_dbl;

// API Application Program interface

stack_dbl* sdbl_create(int max_len);
void sdbl_destroy(stack_dbl* sdbl);
int sdbl_is_empty(stack_dbl* sdbl);
int sdbl_push(stack_dbl* sdbl, double val);
double sdbl_pop(stack_dbl* sdbl);
int sdbl_shrink_if_needed(stack_dbl* sdbl);
double sdbl_top(stack_dbl* sdbl);