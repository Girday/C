#pragma once

#include "../binaryTree/tree.h"

typedef struct {
    tree* buf;
    int size;
    int capacity;
} vector_tree;

vector_tree* vtree_create(int capacity);
void vtree_destroy(vector_tree* vtree);
int vtree_push_back(vector_tree* vtree, tree node);
tree vtree_get(vector_tree* vtree, int index);
int vtree_get_size(vector_tree* vtree);
