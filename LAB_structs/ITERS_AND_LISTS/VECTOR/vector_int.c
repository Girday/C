#include "vector_int.h"
#include <stdlib.h>

vector_int* vint_create(int size) {

    vector_int* res = malloc(sizeof(vector_int));

    if (res == NULL) 
        return NULL;
    
    res -> buf = malloc(sizeof(int) * size);

    if (size && res -> buf == NULL) {
        free(res);
        return NULL;
    }

    res -> size = size;

    return res;

}

void vint_destroy(vector_int* v) {
    free(v -> buf);
    free(v);
}

int vint_get_size(vector_int* v) {
    return v -> size;
}

int vint_set_size(vector_int* v, int size) {
    
    int* new_buf = realloc(v -> buf, sizeof(int) * size);

    if (size && new_buf == NULL)
        return 0;

    v -> buf = new_buf;

    for (int i = v -> size; i < size; i++)
        v -> buf[i] = 0;

    v -> size = size;

    return 1;

}

int vint_get(vector_int* v, int i) {
    return v -> buf[i];
}

void vint_set(vector_int* v, int i, int val) {
    v -> buf[i] = val;
}
