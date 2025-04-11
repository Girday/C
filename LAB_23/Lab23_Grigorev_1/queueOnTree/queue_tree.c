#include "queue_tree.h"
#include <stdio.h>
#include <stdlib.h>

queue_tree* qtree_create(int max_len) {
    queue_tree* res = malloc(sizeof(queue_tree));

    if (res == NULL) {
        fprintf(stderr, "Creating queue of trees failed\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(tree) * max_len);

    if (res -> buf == NULL) {
        fprintf(stderr, "Creating queue of trees failed\n");
        free(res);
        return NULL;
    }

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;
}

void qtree_destroy(queue_tree* qtree) {
    free(qtree -> buf);
    free(qtree);
}

int qtree_is_empty(queue_tree* qtree) {
    return qtree -> len == 0;
}

static int grow(queue_tree* qtree) {
    int new_max_len = qtree -> max_len * 2;
    tree* new_buf = realloc(qtree -> buf, sizeof(tree) * new_max_len);

    if (new_buf == NULL)
        return 0;

    if (qtree -> start + qtree -> len > qtree -> max_len) {
        int elements_to_move = (qtree -> start + qtree -> len) % qtree -> max_len;
        
        for (int i = 0; i < elements_to_move; i++)
            new_buf[qtree -> max_len + i] = new_buf[i];
    }

    qtree -> buf = new_buf;
    qtree -> max_len = new_max_len;
    
    return 1;
}

int qtree_push(queue_tree* qtree, tree val) {
    if (qtree -> len == qtree -> max_len)
        if (!grow(qtree))
            return 0;

    int end = (qtree -> start + qtree -> len) % qtree -> max_len;
    qtree -> buf[end] = val;
    qtree -> len++;

    return 1;
}

tree qtree_pop(queue_tree* qtree) {
    if (qtree_is_empty(qtree)) {
        fprintf(stderr, "Queue of trees is empty\n");
        return NULL;
    }

    tree elem = qtree -> buf[qtree -> start];
    qtree -> start = (qtree -> start + 1) % qtree -> max_len;
    qtree -> len--;

    return elem;
}

int qtree_get_size(queue_tree* qtree) {
    return qtree -> len;
}