#include "tree.h"
#include <stdlib.h>

tree createEmpty() {
    return NULL;
}

int isEmpty(tree t) {
    return t == NULL;
}

double getValue(tree t) {
    return t -> val;
}

tree getLeft(tree t) {
    return t -> left;
}

tree getRight(tree t) {
    return t -> right;
}

tree build(double val, tree left, tree right) {
    tree res = malloc(sizeof(treeNode));

    if (res == NULL) 
        return NULL;
    
    res -> val = val;
    res -> left = left;
    res -> right = right;
    
    return res;
}

void destroy(tree t) {
    if (!isEmpty(t))
        free(t);
}

void destroyRecursive(tree t) {
    if (isEmpty(t))
        return;

    destroyRecursive(getLeft(t));
    destroyRecursive(getRight(t));

    destroy(t);
}

tree add(tree t, double val) {
    if (isEmpty(t))
        return build(val, createEmpty(), createEmpty());
    
    if (val < getValue(t)) {
        tree left = add(getLeft(t), val);
        tree res = build(getValue(t), left, getRight(t));
        
        destroy(t);

        return res;
    } 

    else if (val > getValue(t)) {
        tree right = add(getRight(t), val);
        tree res = build(getValue(t), getLeft(t), right);
        
        destroy(t);
        
        return res;
    } 

    else 
        return t;
}

tree removeNode(tree t, double val) {
    if (isEmpty(t))
        return t;
    
    if (val < getValue(t)) {
        tree left = removeNode(getLeft(t), val);
        tree res = build(getValue(t), left, getRight(t));
        
        destroy(t);
        
        return res;
    } 

    else if (val > getValue(t)) {
        tree right = removeNode(getRight(t), val);
        tree res = build(getValue(t), getLeft(t), right);
        
        destroy(t);
        
        return res;
    }
    
    if (isEmpty(getLeft(t))) {
        tree res = getRight(t);
        destroy(t);
        
        return res;
    } 

    else if (isEmpty(getRight(t))) {
        tree res = getLeft(t);
        destroy(t);
        
        return res;
    }
    
    tree maxLeft = getLeft(t);

    while (!isEmpty(getRight(maxLeft)))
        maxLeft = getRight(maxLeft);
    
    double maxLeftVal = getValue(maxLeft);
    
    tree left = removeNode(getLeft(t), maxLeftVal);
    tree res = build(maxLeftVal, left, getRight(t));
    
    destroy(t);

    return res;
}