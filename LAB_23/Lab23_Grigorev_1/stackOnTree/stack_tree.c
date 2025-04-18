#include "stack_tree.h"
#include <stdlib.h>
#include <stdio.h>

stack_tree* stree_create(int max_len) {

    stack_tree* res = malloc(sizeof(stack_tree));

    if (res == NULL) {
        fprintf(stderr, "Creating stack of tree is failed\n\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(tree) * max_len);

    if (res -> buf == NULL) {
        fprintf(stderr, "Creating stack of tree is failed\n\n");
        free(res);

        return NULL;
    }

    res -> len = 0;
    res -> max_len = max_len;

    return res;
}

void stree_destroy(stack_tree* stree) {
    free(stree -> buf);
    free(stree);
}

int stree_is_empty(stack_tree* stree) {
    return stree -> len == 0;
}

int stree_get_size(stack_tree* stree) {
    return stree -> len;
}

tree stree_pop(stack_tree* stree) {
    if (stree_is_empty(stree)) {
        fprintf(stderr, "Stack of tree is empty\n\n");
        exit(-1);
    }

    tree elem = stree -> buf[stree -> len - 1];
    stree -> len--;

    return elem;
}

static int grow(stack_tree* stree) {
    int new_max_len = stree -> max_len * 2; // 2 - лютая константа с кайфом

    tree* new_buf = realloc(stree -> buf, sizeof(tree) * new_max_len);

    if (new_buf == NULL)
        return 0;
    
    stree -> buf = new_buf;
    stree -> max_len = new_max_len;

    return 1;
}

int stree_push(stack_tree* stree, tree val) {
    if (stree -> len == stree -> max_len)
        if (!grow(stree))
            return 0;

    stree -> buf[stree -> len] = val;
    stree -> len++;

    return 1;
}

int stree_shrink_if_needed(stack_tree* stree) {
    int new_max_len;

    if (stree -> len <= stree -> max_len / 4)
            new_max_len = stree -> max_len / 2;
    else
        return 0;

    tree* new_buf = realloc(stree -> buf, sizeof(tree) * new_max_len);
    
    stree -> buf = new_buf;
    stree -> max_len = new_max_len;

    return 1;
}

tree stree_top(stack_tree* stree) {
    tree elem = stree_pop(stree);
    stree_push(stree, elem);

    return elem;
}
