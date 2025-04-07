#include "deque_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

deque_str* dstr_create(int max_len) {
    deque_str* res = malloc(sizeof(deque_str));
    
    if (res == NULL) {
        fprintf(stderr, "Creating deque of strings failed\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(char*) * max_len);
    
    if (res -> buf == NULL) {
        fprintf(stderr, "Creating deque of strings failed\n");
        free(res);
        return NULL;
    }

    for (int i = 0; i < max_len; i++)
        res -> buf[i] = NULL;

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;
}

void dstr_destroy(deque_str* dstr) {
    if (dstr == NULL) 
        return;
    
    for (int i = 0; i < dstr -> max_len; i++)
        if (dstr -> buf[i] != NULL)
            free(dstr -> buf[i]);

    free(dstr -> buf);
    free(dstr);
}

int dstr_is_empty(deque_str* dstr) {
    return dstr -> len == 0;
}

char* dstr_pop_back(deque_str* dstr) {
    if (dstr_is_empty(dstr)) {
        fprintf(stderr, "Deque of strings is empty\n");
        exit(-1);
    }

    int index = (dstr -> start + dstr -> len - 1) % dstr -> max_len;
    char* elem = dstr -> buf[index];

    dstr -> buf[index] = NULL;
    dstr -> len--;

    return elem;
}

char* dstr_pop_front(deque_str* dstr) {
    if (dstr_is_empty(dstr)) {
        fprintf(stderr, "Deque of strings is empty\n");
        exit(-1);
    }

    char* elem = dstr -> buf[dstr -> start];
    
    dstr -> buf[dstr -> start] = NULL;
    dstr -> start = (dstr -> start + 1) % dstr -> max_len;
    dstr -> len--;

    return elem;
}

static int grow(deque_str* dstr) {
    int new_max_len = dstr -> max_len * 2;
    char** new_buf = malloc(sizeof(char*) * new_max_len);
    
    if (new_buf == NULL)
        return 0;

    for (int i = 0; i < new_max_len; i++)
        new_buf[i] = NULL;


    for (int i = 0; i < dstr -> len; i++) {
        int old_index = (dstr -> start + i) % dstr -> max_len;
        new_buf[i] = dstr -> buf[old_index];
        dstr -> buf[old_index] = NULL;
    }

    free(dstr -> buf);
    dstr -> buf = new_buf;
    dstr -> start = 0;
    dstr -> max_len = new_max_len;
    
    return 1;
}

int dstr_push_back(deque_str* dstr, const char* val) {
    if (dstr -> len == dstr -> max_len)
        if (!grow(dstr))
            return 0;
    
    int index = (dstr -> start + dstr -> len) % dstr -> max_len;
    dstr -> buf[index] = strdup(val);
    
    if (dstr -> buf[index] == NULL)
        return 0;
    
    dstr -> len++;
    return 1;
}

int dstr_push_front(deque_str* dstr, const char* val) {
    if (dstr -> len == dstr -> max_len)
        if (!grow(dstr))
            return 0;

    dstr -> start = (dstr -> start - 1 + dstr -> max_len) % dstr -> max_len;
    dstr -> buf[dstr -> start] = strdup(val);

    if (dstr -> buf[dstr -> start] == NULL) {
        dstr -> start = (dstr -> start + 1) % dstr -> max_len;
        return 0;
    }
    
    dstr -> len++;
    return 1;
}

int dstr_shrink_if_needed(deque_str* dstr) {
    int new_max_len;
    
    if (dstr -> len <= dstr -> max_len / 4) {
        new_max_len = dstr -> max_len / 2;
        
        if (new_max_len < 4)
            new_max_len = 4;
    } 
    
    else 
        return 0;
    

    char** new_buf = malloc(sizeof(char*) * new_max_len);

    if (new_buf == NULL)
        return 0;

    for (int i = 0; i < new_max_len; i++)
        new_buf[i] = NULL;

    for (int i = 0; i < dstr -> len; i++) {
        int old_index = (dstr -> start + i) % dstr -> max_len;
        new_buf[i] = dstr -> buf[old_index];
        dstr -> buf[old_index] = NULL; 
    }

    free(dstr -> buf);
    
    dstr -> buf = new_buf;
    dstr -> start = 0;
    dstr -> max_len = new_max_len;
    
    return 1;
}