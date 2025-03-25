#include "absolut_dbl.h"
#include <stdlib.h>

svector_dbl* svdbl_create(int size) {

    svector_dbl* res = malloc(sizeof(svector_dbl));

    if (res == NULL)
        return NULL;
    
    res -> buf = malloc(sizeof(double) * size);

    if (size && res -> buf == NULL) {
        free(res);
        return NULL;
    }

    res -> max_size = size;
    res -> size = size;
    res -> start = 0;

    return res;

}

void svdbl_destroy(svector_dbl* sv) {
    free(sv -> buf);
    free(sv);
}

int svdbl_get_size(svector_dbl* sv) {
    return sv -> size;
}

int svdbl_set_size(svector_dbl* sv, int size) {

    if (size <= sv -> max_size) {
    
        for (int i = sv -> size; i < size; i++)
            sv -> buf[(sv -> start + i) % sv -> max_size] = 0; 

        sv -> size = size;

        return 1;
    
    }

    double* new_buf = malloc(sizeof(double) * size);

    if (size && new_buf == NULL)
        return 0;

    for (int i = 0; i < sv -> size; i++) 
        new_buf[i] = sv -> buf[(i + sv -> start) % sv -> max_size];

    for (int i = sv -> size; i < size; i++) 
        new_buf[i] = 0;
    
    free(sv -> buf);

    sv -> buf = new_buf;
    sv -> size = size;
    sv -> max_size = size;
    sv -> start = 0;

    return 1;

}

double svdbl_get(svector_dbl* sv, int i) {
    return sv -> buf[i];
}

double svdbl_set(svector_dbl* sv, int i, double val) {
    sv -> buf[i] = val;
}

int svdbl_is_empty(svector_dbl* sv) {
    return sv -> size == 0;
}

double svdbl_pop_back(svector_dbl* sv) {
    
    if (svdbl_is_empty(sv))
        exit(-1);
    
    double elem = sv -> buf[(sv -> start + sv -> size - 1) % sv -> max_size];
    sv -> size--;

    return elem;

}

double svdbl_pop_front(svector_dbl* sv) {

    if (svdbl_is_empty(sv))
        exit(-1);
    
    double elem = sv -> buf[sv -> start];
    sv -> start = (sv -> start + 1) % sv -> max_size;
    sv -> size--;

    return elem;


}

static int grow(svector_dbl* sv) {

    int new_max_size = sv -> max_size * 2;

    double* new_buf = realloc(sv -> buf, sizeof(double) * new_max_size);

    if (new_buf == NULL)
        return 0;

    for (int i = sv -> max_size - 1; i >= sv -> start; i--)
        new_buf[new_max_size - sv -> max_size + i] = new_buf[i];

    sv -> start += new_max_size - sv -> max_size;
    sv -> buf = new_buf;
    sv -> max_size = new_max_size;
        
    return 1;

}

int svdbl_push_back(svector_dbl* sv, double val) {

    if (sv -> size == sv -> max_size)
        if (!grow(sv))
            return 0;
    
    sv -> buf[(sv -> start + sv -> size) % sv -> max_size] = val;
    sv -> size++;

    return 1;

}

int svdbl_push_front(svector_dbl* sv, double val) {

    if  (sv -> size == sv -> max_size)
        if (!grow(sv))
            return 0;

    sv -> start = (sv -> start + sv -> max_size - 1) % sv -> max_size;
    sv -> buf[sv -> start] = val;
    sv -> size++;

    return 1;

}
