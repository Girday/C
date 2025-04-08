#pragma once

typedef struct {
    int* buf;
    int size;
} vector_int;

vector_int* vint_create(int size);
void vint_destroy(vector_int* v);
int vint_get_size(vector_int* v);
int vint_set_size(vector_int* v, int size);
int vint_get(vector_int* v, int i);
void vint_set(vector_int* v, int i, int val);
