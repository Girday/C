#pragma once

#include "../treeStruct/tree.h"

typedef struct {
    tree* buf;
    int len;
    int max_len;
} stack_tree;

stack_tree* stree_create(int max_len);
void stree_destroy(stack_tree* stree);
int stree_is_empty(stack_tree* stree);
int stree_push(stack_tree* stree, tree val);
tree stree_pop(stack_tree* stree);
int stree_shrink_if_needed(stack_tree* stree);
tree stree_top(stack_tree* stree);