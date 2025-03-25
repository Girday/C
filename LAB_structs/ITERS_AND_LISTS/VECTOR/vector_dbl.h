#pragma once

typedef struct {
    double* buf;
    int size;
} vector_dbl;

vector_dbl* vdbl_create(int size);
void vdbl_destroy(vector_dbl* v);
int vdbl_get_size(vector_dbl* v);
int vdbl_set_size(vector_dbl* v, int size);
double vdbl_get(vector_dbl* v, int i);
void vdbl_set(vector_dbl* v, int i, double val);
