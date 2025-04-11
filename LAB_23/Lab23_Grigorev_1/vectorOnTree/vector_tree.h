#pragma once

#include "../treeStruct/tree.h"

typedef struct {
    tree* buf;
    int size;
} vector_tree;

vector_tree* vtree_create(int size);
void vtree_destroy(vector_tree* v);
int vtree_get_size(vector_tree* v);
int vtree_set_size(vector_tree* v, int size);
tree vtree_get(vector_tree* v, int i);
void vtree_set(vector_tree* v, int i, tree val);