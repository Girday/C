#pragma once

#include "../token/token.h"

typedef struct treeNode treeNode;
struct treeNode {
    Token token;
    treeNode *left;
    treeNode *right;
};

typedef treeNode* tree;

tree createEmpty();
tree build(Token token, tree left, tree right);
int isEmpty(tree t);
Token getValue(tree t);
tree getLeft(tree t);
tree getRight(tree t);
void destroyTree(tree t);

void applyReorder(tree* t);

void printTreePretty(tree t, int level);
void deleteUnitMultiply(tree* t);
