#pragma once

#include "..\..\LAB_structs\ITERS_AND_LISTS\VECTOR\vector_int.h"
#include <stdlib.h>

typedef struct treeNode treeNode;
struct treeNode {
    double val;
    treeNode *left;
    treeNode *right;
};

typedef treeNode *tree;

tree createEmpty();
tree build(double val, tree left, tree right);
int isEmpty(tree t);
double getValue(tree t);
tree getLeft(tree t);
tree getRight(tree t);
void destroy(tree t);
void destroyRecursive(tree t);

// tree add(tree t, double val);
int add(tree *t, double val);
tree removeNode(tree t, double val);

int getDepth(tree t);
int levelWidth(tree t, int k);
int getWidthByBFS(tree t);
int getWidthByVector(tree t);
