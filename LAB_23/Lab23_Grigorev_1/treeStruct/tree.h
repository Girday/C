#pragma once

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
void destroyTree(tree t);
void setLeft(tree t, tree left);
void setRight(tree t, tree right);

int addNode(tree *t, double val);
// tree addNode(tree t, double val);
tree removeNode(tree t, double val);

int getDepth(tree t);
int levelWidth(tree t, int k);
int getWidthByBFS(tree t);
int getWidthByVector(tree t);
int getLevel(tree t, double val);

int checkAVL(tree t);