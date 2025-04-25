#include <stdlib.h>

#include "vector_tree.h"

vector_tree* vtree_create(int capacity) {
    vector_tree* vtree = malloc(sizeof(vector_tree));

    vtree -> buf = malloc(sizeof(tree) * capacity);
    vtree -> size = 0;
    vtree -> capacity = capacity;

    return vtree;
}

void vtree_destroy(vector_tree* vtree) {
    free(vtree -> buf);
    free(vtree);
}

int vtree_push_back(vector_tree* vtree, tree node) {
    if (vtree -> size >= vtree -> capacity) {
        vtree -> capacity *= 2;
        vtree -> buf = realloc(vtree -> buf, sizeof(tree) * vtree -> capacity);
    }

    vtree -> buf[vtree -> size++] = node;
    
    return 1;
}

tree vtree_get(vector_tree* vtree, int index) {
    return vtree -> buf[index];
}

int vtree_get_size(vector_tree* vtree) {
    return vtree -> size;
}
