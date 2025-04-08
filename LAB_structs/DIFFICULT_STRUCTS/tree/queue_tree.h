#pragma once

#include "..\..\..\LAB_23\BinarySearchTree\tree.h"

typedef struct {
    tree* buf;
    int len;
    int max_len;
    int start;
} queue_tree;

queue_tree* qtree_create(int max_len);
void qtree_destroy(queue_tree* qtree);
int qtree_is_empty(queue_tree* qtree);
int qtree_push(queue_tree* qtree, tree val);
tree qtree_pop(queue_tree* qtree);
int qtree_get_size(queue_tree* qtre);