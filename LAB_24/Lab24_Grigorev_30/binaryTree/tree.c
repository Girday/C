#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "../vectorOnInt/vector_int.h"
#include "../queueOnTree/queue_tree.h"
#include "../stackOnTree/stack_tree.h"
#include "../vectorOnTree/vector_tree.h"

tree createEmpty() {
    return NULL;
}

int isEmpty(tree t) {
    return t == NULL;
}

Token getValue(tree t) {
    return t -> token;
}

tree getLeft(tree t) {
    return t -> left;
}

tree getRight(tree t) {
    return t -> right;
}

tree build(Token token, tree left, tree right) {
    tree res = malloc(sizeof(treeNode));
    
    if (res == NULL) 
        return NULL;
    
    res -> token = token;
    res -> left = left;
    res -> right = right;
    
    return res;
}

static void destroy(tree t) {
    if (!isEmpty(t)) 
        free(t);
}

void destroyTree(tree t) {
    if (t == NULL) 
        return;
    
    queue_tree* q = qtree_create(1);
    qtree_push_back(q, t);
    
    while (!qtree_is_empty(q)) {
        tree cur = qtree_pop_front(q);
    
        if (getLeft(cur) != NULL) 
            qtree_push_back(q, getLeft(cur));
        
        if (getRight(cur) != NULL) 
            qtree_push_back(q, getRight(cur));
    
        free(cur -> token.value);
        free(cur);
    }

    qtree_destroy(q);
}

void printTreePretty(tree t, int level) {
    if (isEmpty(t)) 
        return;
    
    printTreePretty(getRight(t), level + 1);
    
    for (int i = 0; i < level; i++) 
        printf("    ");
    
    printf("%s\n", getValue(t).value);
    printTreePretty(getLeft(t), level + 1);
}

void deleteUnitMultiply(tree* t) {
    if (isEmpty(*t)) 
        return;

    deleteUnitMultiply(&(*t)->left);
    deleteUnitMultiply(&(*t)->right);

    if ((*t) -> token.type == TOK_OP && strcmp((*t) -> token.value, "*") == 0) {
        if ((*t) -> left != NULL && (*t) -> left -> token.type == TOK_CONST && strcmp((*t) -> left -> token.value, "1") == 0) {
            tree tmp = *t;
            *t = (*t) -> right;

            destroyTree(tmp -> left);
            free(tmp -> token.value);
            free(tmp);
        } 
        else if ((*t) -> right != NULL && (*t) -> right -> token.type == TOK_CONST && strcmp((*t) -> right -> token.value, "1") == 0) {
            tree tmp = *t;
            *t = (*t) -> left;

            destroyTree(tmp -> right);
            free(tmp -> token.value);
            free(tmp);
        }
    }
}

static void collectOperands(tree t, TokenType opType, vector_tree* operands) {
    if (isEmpty(t)) 
        return;
    
    if (t -> token.type == TOK_OP && strcmp(t -> token.value, opType == TOK_OP ? "+" : "*") == 0) {
        collectOperands(t -> left, opType, operands);
        collectOperands(t -> right, opType, operands);
    } 
    else
        vtree_push_back(operands, t);
}

static tree reorderOperands(tree t) {
    if (isEmpty(t) || t -> token.type != TOK_OP) 
        return t;

    char* op = t -> token.value;
    
    if (strcmp(op, "+") != 0 && strcmp(op, "*") != 0) 
        return t;

    vector_tree* operands = vtree_create(10);
    collectOperands(t, t -> token.type, operands);

    vector_tree* constants = vtree_create(10);
    vector_tree* variables = vtree_create(10);
    
    for (int i = 0; i < vtree_get_size(operands); i++) {
        tree node = vtree_get(operands, i);
        
        if (node -> token.type == TOK_CONST)
            vtree_push_back(constants, node); 
        else
            vtree_push_back(variables, node);
    }

    tree newTree = NULL;

    for (int i = 0; i < vtree_get_size(constants); i++) {
        tree node = vtree_get(constants, i);
        newTree = newTree ? build(t->token, newTree, node) : node;
    }

    for (int i = 0; i < vtree_get_size(variables); i++) {
        tree node = vtree_get(variables, i);
        newTree = newTree ? build(t->token, newTree, node) : node;
    }

    vtree_destroy(operands);
    vtree_destroy(constants);
    vtree_destroy(variables);
    
    return newTree;
}

void applyReorder(tree* t) {
    if (isEmpty(*t)) 
        return;
    
    *t = reorderOperands(*t);
    
    applyReorder(&(*t) -> left);
    applyReorder(&(*t) -> right);
}
