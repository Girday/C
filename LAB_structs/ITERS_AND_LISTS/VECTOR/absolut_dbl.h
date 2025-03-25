#pragma once

typedef struct {
    double* buf;
    int max_size;
    int size;
    int start;
} svector_dbl;

svector_dbl* svdbl_create(int size);
void svdbl_destroy(svector_dbl* sv);
int svdbl_get_size(svector_dbl* sv);
int svdbl_set_size(svector_dbl* sv, int size);
double svdbl_get(svector_dbl* sv, int i);
double svdbl_set(svector_dbl* sv, int i, double val);

int svdbl_is_empty(svector_dbl* sv);
int svdbl_push_back(svector_dbl* sv, double val);
int svdbl_push_front(svector_dbl* sv, double val);
double svdbl_pop_back(svector_dbl* sv);
double svdbl_pop_front(svector_dbl* sv);
