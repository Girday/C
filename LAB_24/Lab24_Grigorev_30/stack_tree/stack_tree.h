#pragma once

#include "../binaryTree/tree.h"

typedef struct {
    tree* buf;
    int max_len;
    int len;
} stack_tree;

stack_tree* stree_create(int max_len);
void stree_destroy(stack_tree* stree);
int stree_is_empty(stack_tree* stree);
int stree_push_back(stack_tree* stree, tree value);
tree stree_pop_back(stack_tree* stree);
tree stree_top(stack_tree* stree);