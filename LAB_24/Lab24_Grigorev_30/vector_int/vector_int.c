#include <stdlib.h>

#include "vector_int.h"

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

void vint_destroy(vector_int* vint) {
    free(vint -> buf);
    free(vint);
}

int vint_get_size(vector_int* vint) {
    return vint -> size;
}

int vint_set_size(vector_int* vint, int size) {
    int* new_buf = realloc(vint -> buf, sizeof(int) * size);
    
    if (size && new_buf == NULL) 
        return 0;
    
    vint -> buf = new_buf;
    
    for (int i = vint -> size; i < size; i++) 
        vint -> buf[i] = 0;
    
    vint -> size = size;
    
    return 1;
}

int vint_get(vector_int* vint, int i) {
    return vint -> buf[i];
}

void vint_set(vector_int* vint, int i, int val) {
    vint -> buf[i] = val;
}

int vint_push_back(vector_int* vint, int val) {
    if (!vint_set_size(vint, vint_get_size(vint) + 1)) 
        return 0;
    
    vint_set(vint, vint_get_size(vint) - 1, val);
    
    return 1;
}

int vint_pop_back(vector_int* vint) {
    int val = vint_get(vint, vint_get_size(vint) - 1);
    vint_set_size(vint, vint_get_size(vint) - 1);
    
    return val;
}