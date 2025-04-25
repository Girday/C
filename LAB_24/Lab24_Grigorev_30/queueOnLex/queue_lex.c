#include "queue_lex.h"
#include <stdlib.h>
#include <string.h>

queue_lex* qlex_create(int max_len) {
    queue_lex* res = malloc(sizeof(queue_lex));
    
    if (res == NULL) 
        return NULL;

    res -> max_len = max_len;
    res -> buf = malloc(sizeof(Token) * max_len);
    
    if (res -> buf == NULL) {
        free(res);
        return NULL;
    }
    
    res -> len = 0;
    res -> start = 0;
    
    return res;
}

static int grow(queue_lex* qlex) {
    int new_max_len = qlex -> max_len * 2;
    Token* new_buf = realloc(qlex -> buf, sizeof(Token) * new_max_len);
    
    if (new_buf == NULL) 
        return 0;
    
    for (int i = qlex -> max_len - 1; i >= qlex -> start; i--)
        new_buf[new_max_len - qlex -> len + i] = new_buf[i];
    
    qlex -> start += new_max_len - qlex -> max_len;
    qlex -> buf = new_buf;
    qlex -> max_len = new_max_len;
    
    return 1;
}

void qlex_destroy(queue_lex* qlex) {
    if (!qlex) 
        return;
    
    for (int i = 0; i < qlex -> len; i++)
        free(qlex -> buf[(qlex -> start + i) % qlex -> max_len].value); // Освобождаем строки
    
    free(qlex -> buf);
    free(qlex);
}

int qlex_is_empty(queue_lex* qlex) {
    return qlex -> len == 0;
}

int qlex_push_back(queue_lex* qlex, Token value) {
    if (qlex -> len == qlex -> max_len)
        if (!grow(qlex)) 
            return 0;

    qlex -> buf[(qlex -> len + qlex -> start) % qlex -> max_len] = value;
    qlex -> len++;
    
    return 1;
}

Token qlex_pop_front(queue_lex* qlex) {
    Token value = qlex -> buf[qlex -> start];
    
    qlex -> start = (qlex -> start + 1) % qlex -> max_len;
    qlex -> len--;
    
    return value;
}

Token qlex_top(queue_lex* qlex) {
    return qlex -> buf[qlex -> start];
}
