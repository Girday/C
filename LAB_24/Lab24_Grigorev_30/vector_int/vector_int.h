#pragma once

typedef struct {
    int* buf;
    int size;
} vector_int;

vector_int* vint_create(int size);
void vint_destroy(vector_int* vint);
int vint_get_size(vector_int* vint);
int vint_set_size(vector_int* vint, int size);
int vint_get(vector_int* vint, int i);
void vint_set(vector_int* vint, int i, int val);

int vint_push_back(vector_int* vint, int val);
int vint_pop_back(vector_int* vint);