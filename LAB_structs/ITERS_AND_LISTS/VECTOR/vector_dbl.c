#include "vector_dbl.h"
#include <stdlib.h>

vector_dbl* vdbl_create(int size) {

    vector_dbl* res = malloc(sizeof(vector_dbl));

    if (res == NULL) 
        return NULL;
    
    res -> buf = malloc(sizeof(double) * size);

    if (size && res -> buf == NULL) {
        free(res);
        return NULL;
    }

    res -> size = size;

    return res;

}

void vdbl_destroy(vector_dbl* v) {
    free(v -> buf);
    free(v);
}

int vdbl_get_size(vector_dbl* v) {
    return v -> size;
}

int vdbl_set_size(vector_dbl* v, int size) {
    
    double* new_buf = realloc(v -> buf, sizeof(double) * size);

    if (size && new_buf == NULL)
        return 0;

    v -> buf = new_buf;

    for (int i = v -> size; i < size; i++)
        v -> buf[i] = 0;

    v -> size = size;

    return 1;

}

double vdbl_get(vector_dbl* v, int i) {
    return v -> buf[i];
}

void vdbl_set(vector_dbl* v, int i, double val) {
    v -> buf[i] = val;
}
