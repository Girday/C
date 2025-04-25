#pragma once

#include "../binaryTree/tree.h"

typedef struct {
    tree* buf;
    int max_len;
    int len;
    int start;
} queue_tree;

queue_tree* qtree_create(int max_len);
void qtree_destroy(queue_tree* qtree);
int qtree_is_empty(queue_tree* qtree);
int qtree_get_size(queue_tree* qtree);
int qtree_push_back(queue_tree* qtree, tree value);
tree qtree_top(queue_tree* qtree);
tree qtree_pop_front(queue_tree* qtree);
