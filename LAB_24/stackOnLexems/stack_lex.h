#pragma once

typedef struct {
    char* buf;
    int len;
    int max_len;
} stack_lex;

// API Application Program interface

stack_lex* slex_create(int max_len);
void slex_destroy(stack_lex* slex);
int slex_is_empty(stack_lex* slex);
int slex_push(stack_lex* slex, char val);
char slex_pop(stack_lex* slex);
int slex_shrink_if_needed(stack_lex* slex);
char slex_top(stack_lex* slex);
