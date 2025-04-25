#include "queue_lex.h"
#include <stdio.h>
#include <stdlib.h>

queue_lex* qchr_create(int max_len) {

    queue_lex* res = malloc(sizeof(queue_lex));

    if (res == NULL) {
        fprintf(stderr, "Creating queue of char is failed\n\n");        
        return NULL;
    }

    res -> buf = malloc(sizeof(char) * max_len);

    if (res -> buf == NULL) {

        fprintf(stderr, "Creating queue of char is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;

}

void qchr_destroy(queue_lex* qchr) {
    free(qchr -> buf);
    free(qchr);
}

int qchr_is_empty(queue_lex* qchr) {
    return qchr -> len == 0;
}

char qchr_pop(queue_lex* qchr) {

    if (qchr_is_empty(qchr)) {
        fprintf(stderr, "Queue of char is empty\n\n");
        exit(-1);
    }

    char elem = qchr -> buf[qchr -> start];

    qchr -> start = (qchr -> start + 1) % qchr -> max_len;
    qchr -> len--;

    return elem;

}

static int grow(queue_lex* qchr) {

    int new_max_len = qchr -> max_len * 2;

    char* new_buf = realloc(qchr -> buf, sizeof(char) * new_max_len);

    if (new_buf == NULL)
        return 0;

    for (int i = qchr -> max_len - 1; i >= qchr -> start; i--)
        new_buf[new_max_len - qchr -> max_len + i] = new_buf[i];

    qchr -> start += new_max_len - qchr -> max_len;
    qchr -> buf = new_buf;
    qchr -> max_len = new_max_len;
    
    return 1;

}

int qchr_push(queue_lex* qchr, char val) {

    if (qchr -> len == qchr -> max_len)
        if (!grow(qchr))
            return 0;

    qchr -> buf[(qchr -> start + qchr -> len) % qchr -> max_len] = val;
    qchr -> len++;

    return 1;

}

int qchr_shrink_if_needed(queue_lex* qchr) {

    int new_max_len;

    if (qchr -> len <= qchr -> max_len / 4)
            new_max_len = qchr -> max_len / 2;
    else
        return 0;

    if (qchr -> start + qchr -> len >= new_max_len) {
        int cur_len = new_max_len - qchr -> start - 1;

        for (cur_len; cur_len <= qchr -> len; cur_len++)
            qchr -> buf[(qchr -> start + cur_len) % qchr -> max_len] = qchr -> buf[cur_len];
        
    }

    char* new_buf = realloc(qchr -> buf, sizeof(char) * new_max_len);

    qchr -> buf = new_buf;
    qchr -> max_len = new_max_len;
    
    return 1;
}

