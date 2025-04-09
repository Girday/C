#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "./vectorOnInt/vector_int.h"
#include "./queueOnTree/queue_tree.h"

tree createEmpty() {
    return NULL;
}

int isEmpty(tree t) {
    return t == NULL;
}

double getValue(tree t) {
    if (t == NULL) {
        printf("Error: Attempt to get value from NULL node.\n");
        return 0.0;
    }
    
    return t -> val;
}

tree getLeft(tree t) {
    if (t == NULL) {
        printf("Error: Attempt to get left child from NULL node.\n");
        return NULL;
    }

    return t -> left;
}

tree getRight(tree t) {
    if (t == NULL) {
        printf("Error: Attempt to get right child from NULL node.\n");
        return NULL;
    }

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

int add(tree *t, double val) {
    if (*t == NULL) {
        *t = malloc(sizeof(treeNode));

        if (*t == NULL) { 
            printf("Error: Can't add a node (allocation error)\n");
            return 0;
        }

        (*t) -> val = val;
        (*t) -> left = NULL;
        (*t) -> right = NULL;

        return 1;
    }

    if (val < (*t) -> val) 
        return add(&(*t) -> left, val);
    
    if (val > (*t) -> val)
        return add(&(*t) -> right, val);

    return 0;
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

static int max(int a, int b) {
    return a > b ? a : b;
}

int getDepth(tree t) {
    if (t == NULL)
        return 0;
    
    return 1 + max(getDepth(getLeft(t)), getDepth(getRight(t)));
}

int levelWidth(tree t, int k) {
    if (k == 0) {
        if (t != NULL)
            return 1;
    
        return 0;
    }

    return levelWidth(getLeft(t), k - 1) + levelWidth(getRight(t), k - 1);
}

static void widthsVector(tree t, vector_int* vint, int k) {
    if (t == NULL)
        return;
    
    if (vint_get_size(vint) < k + 1)
        vint_set_size(vint, k + 1);
    
    vint_set(vint, k, vint_get(vint, k) + 1);
    widthsVector(getLeft(t), vint, k + 1);
    widthsVector(getRight(t), vint, k + 1);
}

int getWidthByVector(tree t) {
    vector_int* vint = vint_create(0);

    widthsVector(t, vint, 0);
    int res = 0;
    
    for (int i = 0; i < vint_get_size(vint); i++)
        res = max(res, vint_get(vint, i));
    
    vint_destroy(vint);

    return res;
}

int getWidthByBFS(tree t) {
    if (t == NULL)
        return 0;

    queue_tree* q1 = qtree_create(1);
    queue_tree* q2 = qtree_create(1);

    int res = 0;

    qtree_push(q1, t);

    while (!qtree_is_empty(q1)) {
        res = max(res, qtree_get_size(q1));

        while (!qtree_is_empty(q1)) {
            tree cur = qtree_pop(q1);

            if (!isEmpty(getLeft(cur)))
                qtree_push(q2, getLeft(cur));
            
            if (!isEmpty(getRight(cur)))
                qtree_push(q2, getRight(cur));   
        }

        queue_tree* c = q2;
        q2 = q1;
        q1 = c;
    }

    qtree_destroy(q1);
    qtree_destroy(q2);
    
    return res;
}

int checkAVL(tree t, double minH, double maxH) {
    if (t == NULL)
        return 0;

    if (t -> val <= minH || t -> val >= maxH)
        return -1;

    int leftHeight = checkAVL(t -> left, minH, t -> val);
    if (leftHeight == -1)
        return -1;

    int rightHeight = checkAVL(t -> right, t -> val, maxH);
    if (rightHeight == -1)
        return -1;

    if (abs(leftHeight - rightHeight) > 1)
        return -1;

    return 1 + max(leftHeight, rightHeight);
}