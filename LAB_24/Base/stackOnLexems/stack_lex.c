#include "stack_lex.h"
#include <stdlib.h>
#include <stdio.h>

stack_lex* slex_create(int max_len) {
    stack_lex* res = malloc(sizeof(stack_lex));

    if (res == NULL) {
        fprintf(stderr, "Creating stack of char is failed\n\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(char) * max_len);

    if (res -> buf == NULL) {

        fprintf(stderr, "Creating stack of char is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> max_len = max_len;

    return res;
}

void slex_destroy(stack_lex* slex) {
    free(slex -> buf);
    free(slex);
}

int slex_is_empty(stack_lex* slex) {
    return slex -> len == 0;
}

int slex_get_size(stack_lex* slex) {
    return slex -> len;
}

char slex_pop(stack_lex* slex) {
    if (slex_is_empty(slex)) {
        fprintf(stderr, "Stack of char is empty\n\n");
        exit(-1);
    }

    char elem = slex -> buf[slex -> len - 1];
    slex -> len--;

    return elem;
}

static int grow(stack_lex* slex) {
    int new_max_len = slex -> max_len * 2; // 2 - лютая константа с кайфом

    char* new_buf = realloc(slex -> buf, sizeof(char) * new_max_len);

    if (new_buf == NULL)
        return 0;
    
    slex -> buf = new_buf;
    slex -> max_len = new_max_len;

    return 1;
}

int slex_push(stack_lex* slex, char val) {
    if (slex -> len == slex -> max_len)
        if (!grow(slex))
            return 0;

    slex -> buf[slex -> len] = val;
    slex -> len++;

    return 1;
}

int slex_shrink_if_needed(stack_lex* slex) {
    int new_max_len;

    if (slex -> len <= slex -> max_len / 4)
            new_max_len = slex -> max_len / 2;
    else
        return 0;

    char* new_buf = realloc(slex -> buf, sizeof(char) * new_max_len);
    
    slex -> buf = new_buf;
    slex -> max_len = new_max_len;

    return 1;
}

char slex_top(stack_lex* slex) {
    char elem = slex_pop(slex);
    slex_push(slex, elem);

    return elem;
}