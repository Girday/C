#include "deque_dbl.h"
#include <stdio.h>
#include <stdlib.h>

deque_dbl* ddbl_create(int max_len) {

    deque_dbl* res = malloc(sizeof(deque_dbl));

    if (res == NULL) {
        fprintf(stderr, "Creating deque of double is failed\n\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(double) * max_len);

    if (res -> buf == NULL) {
        
        fprintf(stderr, "Creating deque of double is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;

}

void ddbl_destroy(deque_dbl* ddbl) {
    free(ddbl -> buf);
    free(ddbl);
}

int ddbl_is_empty(deque_dbl* ddbl) {
    return ddbl -> len == 0;    
}

double ddbl_pop_back(deque_dbl* ddbl) {

    if (ddbl_is_empty(ddbl)) {
        fprintf(stderr, "Deque of double is empty\n\n");
        exit(-1);
    }

    double elem = ddbl -> buf[(ddbl -> start + ddbl -> len - 1) % ddbl -> max_len];
    ddbl -> len--;

    return elem;

}

double ddbl_pop_front(deque_dbl* ddbl) {

    if (ddbl -> len == 0) {
        fprintf(stderr, "Deque of double is empty\n\n");
        exit(-1);
    }

    double elem = ddbl -> buf[ddbl -> start];
    ddbl -> start = (ddbl -> start + 1) % ddbl -> max_len;
    ddbl -> len--;

    return elem;

}

static int grow(deque_dbl* ddbl) {

    int new_max_len = ddbl -> max_len * 2;

    double* new_buf = realloc(ddbl -> buf, sizeof(double) * new_max_len);

    if (new_buf == NULL)
        return 0;

    for (int i = ddbl -> max_len - 1; i >= ddbl -> start; i--)
        new_buf[new_max_len - ddbl -> max_len + i] = new_buf[i];

    ddbl -> start += new_max_len - ddbl -> max_len;
    ddbl -> buf = new_buf;
    ddbl -> max_len = new_max_len;
    
    return 1;

}

int ddbl_push_back(deque_dbl* ddbl, double val) {

    if (ddbl -> len == ddbl -> max_len)
        if (!grow(ddbl))
            return 0;
    
    ddbl -> buf[(ddbl -> start + ddbl -> len) % ddbl -> max_len] = val;
    ddbl -> len++;

    return 1;

}

int ddbl_push_front(deque_dbl* ddbl, double val) {

    if (ddbl -> len == ddbl -> max_len)
        if (!grow(ddbl))
            return 0;

    ddbl -> start = (ddbl -> start - 1 + ddbl -> max_len) % ddbl -> max_len;
    ddbl -> buf[ddbl -> start] = val;
    ddbl -> len++;

    return 1;

}

int ddbl_shrink_if_needed(deque_dbl* ddbl) {

    int new_max_len;

    if (ddbl -> len <= ddbl -> max_len / 4)
            new_max_len = ddbl -> max_len / 2;
    else
        return 0;

    if (ddbl -> start + ddbl -> len >= new_max_len) {
        
        int cur_len = new_max_len - ddbl -> start - 1;

        for (cur_len; cur_len <= ddbl -> len; cur_len++)
            ddbl -> buf[(ddbl -> start + cur_len) % ddbl -> max_len] = ddbl -> buf[cur_len];
        
    }

    double* new_buf = realloc(ddbl -> buf, sizeof(double) * new_max_len);

    ddbl -> buf = new_buf;
    ddbl -> max_len = new_max_len;
    
    return 1;
}
