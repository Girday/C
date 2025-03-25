#pragma once
#include "../VECTOR/absolut_dbl.h"

typedef struct {
    svector_dbl* sv;
    int i;
} iter;

iter svdbl_begin(svector_dbl* sv);
iter svdbl_end(svector_dbl* sv);
iter svdbl_iter_move_next(iter i);
int svdbl_iter_equal(iter it1, iter it2);
double svdbl_iter_get(iter it);
void svdbl_iter_set(iter it, double val);
