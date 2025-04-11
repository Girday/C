#include "vector_tree.h"
#include <stdlib.h>
#include <stdio.h>

vector_tree* vtree_create(int size) {
    vector_tree* res = malloc(sizeof(vector_tree));
    
    if (res == NULL) {
        fprintf(stderr, "Creating vector of trees failed\n");
        return NULL;
    }
    
    res -> buf = malloc(sizeof(tree) * size);
    
    if (size && res -> buf == NULL) {
        fprintf(stderr, "Creating vector of trees failed\n");
        free(res);
        return NULL;
    }
    
    for (int i = 0; i < size; i++)
        res -> buf[i] = createEmpty();
    
    res -> size = size;

    return res;
}

void vtree_destroy(vector_tree* v) {
    if (v == NULL)
        return;
    
    for (int i = 0; i < v -> size; i++)
        destroyTree(v -> buf[i]);
    
    free(v -> buf);
    free(v);
}

int vtree_get_size(vector_tree* v) {
    return v -> size;
}

int vtree_set_size(vector_tree* v, int size) {
    if (size == v -> size)
        return 1;
    
    if (size < v -> size)
        for (int i = size; i < v -> size; i++)
            destroyTree(v -> buf[i]);
    
    tree* new_buf = realloc(v -> buf, sizeof(tree) * size);
    
    if (size && new_buf == NULL)
        return 0;
    
    v -> buf = new_buf;
    
    for (int i = v -> size; i < size; i++)
        v -> buf[i] = createEmpty();
    
    v -> size = size;
    
    return 1;
}

tree vtree_get(vector_tree* v, int i) {
    return v -> buf[i];
}

void vtree_set(vector_tree* v, int i, tree val) {
    destroyTree(v -> buf[i]);
    v -> buf[i] = val;
}