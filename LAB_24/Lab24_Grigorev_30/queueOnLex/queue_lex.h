#pragma once

#include "../token/token.h"

typedef struct {
    Token* buf;
    int max_len;
    int len;
    int start;
} queue_lex;

queue_lex* qlex_create(int max_len);
void qlex_destroy(queue_lex* qlex);
int qlex_is_empty(queue_lex* qlex);
int qlex_push_back(queue_lex* qlex, Token value);
Token qlex_pop_front(queue_lex* qlex);
Token qlex_top(queue_lex* qlex);
void print_queue(queue_lex* q);