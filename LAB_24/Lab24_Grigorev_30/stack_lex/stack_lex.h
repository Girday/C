#pragma once

#include "../token/token.h"

typedef struct {
    Token* buf; // Изменено с char* на Token*
    int max_len;
    int len;
} stack_lex;

stack_lex* slex_create(int max_len);
void slex_destroy(stack_lex* slex);
int slex_is_empty(stack_lex* slex);
int slex_push_back(stack_lex* slex, Token value); // Изменено char на Token
Token slex_pop_back(stack_lex* slex); // Изменено char на Token
Token slex_top(stack_lex* slex); // Изменено char на Token