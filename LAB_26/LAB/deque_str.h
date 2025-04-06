#pragma once

typedef struct {
    char** buf;
    int len;
    int max_len;
    int start;
} deque_str;

deque_str* dstr_create(int max_len);
void dstr_destroy(deque_str* dstr);
int dstr_is_empty(deque_str* dstr);
int dstr_push_back(deque_str* dstr, const char* val);
int dstr_push_front(deque_str* dstr, const char* val);
char* dstr_pop_back(deque_str* dstr);
char* dstr_pop_front(deque_str* dstr);
int dstr_shrink_if_needed(deque_str* dstr);