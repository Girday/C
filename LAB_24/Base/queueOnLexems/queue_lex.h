#pragma once

typedef struct {
    char* buf;
    int len;
    int max_len;
    int start;
} queue_lex;

queue_lex* qchr_create(int max_len);
void qchr_destroy(queue_lex* qchr);
int qchr_is_empty(queue_lex* qchr);
int qchr_push(queue_lex* qchr, double val);
double qchr_pop(queue_lex* qchr);
int qchr_shrink_if_needed(queue_lex* qchr);
