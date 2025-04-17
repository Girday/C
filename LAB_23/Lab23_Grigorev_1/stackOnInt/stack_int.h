#pragma once

typedef struct {
    int* buf;
    int len;
    int max_len;
} stack_int;

stack_int* sint_create(int max_len);
void sint_destroy(stack_int* sint);
int sint_is_empty(stack_int* sint);
int sint_push(stack_int* sint, int val);
int sint_pop(stack_int* sint);
