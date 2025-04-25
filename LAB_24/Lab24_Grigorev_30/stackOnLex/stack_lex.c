#include "stack_lex.h"
#include <stdlib.h>
#include <string.h>

stack_lex* slex_create(int max_len) {
    stack_lex* res = malloc(sizeof(stack_lex));

    if (res == NULL) 
        return NULL;
 
    res -> max_len = max_len;
    res -> buf = malloc(sizeof(Token) * max_len); // Изменено char на Token
    
    if (res -> buf == NULL) {
        free(res);
        return NULL;
    }

    res -> len = 0;
    
    return res;
}

static int grow(stack_lex* slex) {
    int new_max_len = slex -> max_len * 2;
    Token* new_buf = realloc(slex -> buf, sizeof(Token) * new_max_len); // Изменено char на Token
    
    if (new_buf == NULL) 
        return 0;
    
    slex -> buf = new_buf;
    slex -> max_len = new_max_len;
    
    return 1;
}

void slex_destroy(stack_lex* slex) {
    if (!slex) 
        return;
    
    for (int i = 0; i < slex -> len; i++)
        free(slex -> buf[i].value); // Освобождаем строки токенов
    
    free(slex -> buf);
    free(slex);
}

int slex_is_empty(stack_lex* slex) {
    return slex -> len == 0;
}

int slex_push_back(stack_lex* slex, Token value) {
    if (slex -> len == slex -> max_len)
        if (!grow(slex)) 
            return 0;

    slex -> buf[slex -> len] = value;
    slex -> len++;

    return 1;
}

Token slex_pop_back(stack_lex* slex) {
    slex -> len--;
    return slex -> buf[slex -> len];
}

Token slex_top(stack_lex* slex) {
    return slex -> buf[slex -> len - 1];
}
