#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "../vectorOnInt/vector_int.h"
#include "../vectorOnTree/vector_tree.h"
#include "../queueOnTree/queue_tree.h"


                        /* === ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ === */

static int maximum(int a, int b) {
    return a > b ? a : b;
}


                        /* === API === */ 

// Я понимаю, что это всё находится в API - так просто немножко удобнее

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


                        /* === УНИЧТОЖЕНИЕ ВСЕГО ДЕРЕВА === */

/* === Итеративная реализация === */

/*

void destroyTree(tree t) {
    if (isEmpty(t))
        return;
    

    // 1. Реализовать стек на tree 
    // 2. больше я не придумал (просто while как будто не катит)

}

*/

/* === Рекурсивная реализация === */

void destroyTree(tree t) {
    if (isEmpty(t))
        return;

    destroyTree(getLeft(t));
    destroyTree(getRight(t));

    destroy(t);
}


                        /* === ДОБАВЛЕНИЕ УЗЛА === */

/* === Итеративная реализация === */

int add(tree *t, double val) {
    treeNode **current = t;

    while (*current != NULL) {
        if (val < (*current) -> val) {
            current = &(*current) -> left;
        } else if (val > (*current) -> val) {
            current = &(*current) -> right;
        } else {
            return 0;
        }
    }
    
    *current = malloc(sizeof(treeNode));
    
    if (*current == NULL) {
        printf("Error: Can't add a node (allocation error)\n");
        return 0;
    }
    
    (*current) -> val = val;
    (*current) -> left = NULL;
    (*current) -> right = NULL;
    
    return 1;
}


/*
    === Рекурсивная реализация ===

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

*/


                        /* === УДАЛЕНИЕ УЗЛА === */

/* === Итеративная реализация === */

tree removeNode(tree t, double val) {
    tree current = t;
    tree parent = NULL;
    
    // Поиск узла и родителя
    while (current != NULL && current -> val != val) {
        parent = current;
        current = (val < current -> val) ? current -> left : current -> right;
    }
    
    if (current == NULL) return t; // Узел не найден
    
    // Случай 1: Нет детей или один ребенок
    if (current -> left == NULL || current -> right == NULL) {
        tree child = (current -> left != NULL) ? current -> left : current -> right;
        
        if (parent == NULL) {
            free(current);
            return child;
        }
        
        if (parent -> left == current) parent -> left = child;
        else parent -> right = child;
        free(current);
    }
    // Случай 2: Два ребенка
    else {
        tree successor = current -> right;
        tree successorParent = current;
        
        while (successor -> left != NULL) {
            successorParent = successor;
            successor = successor -> left;
        }
        
        current -> val = successor -> val;
        
        if (successorParent -> left == successor) 
            successorParent -> left = successor -> right;
        else 
            successorParent -> right = successor -> right;
        
        free(successor);
    }
    
    return t;
}

/*
    === Рекурсивная реализация ===

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

*/


                        /* === ГЛУБИНА ДЕРЕВА === */

/* === Итеративная реализация === */

/* === Рекурсивная реализация === */

int getDepth(tree t) {
    if (t == NULL)
        return 0;
    
    return 1 + maximum(getDepth(getLeft(t)), getDepth(getRight(t)));
}


                        /* === ШИРИНА КОНКРЕТНОГО УРОВНЯ === */

/*

1. levelWidth будет итерироваться до определённого уровня
2. На нужном уровне будет вызывать getWidthByBFS
3. getWidthByBFS без рекурсии вычисляет ширину поддерева

*/

int levelWidth(tree t, int k) {
    if (k == 0) {
        if (t != NULL)
            return 1;
    
        return 0;
    }

    return levelWidth(getLeft(t), k - 1) + levelWidth(getRight(t), k - 1);
}

int getWidthByBFS(tree t) {
    if (t == NULL)
        return 0;

    queue_tree* q1 = qtree_create(1);
    queue_tree* q2 = qtree_create(1);

    int res = 0;

    qtree_push(q1, t);

    while (!qtree_is_empty(q1)) {
        res = maximum(res, qtree_get_size(q1));

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


                        /* === ПРОВЕРКА НА СБАЛАНСИРОВАННОСТЬ (AVL) === */

/* === Итеративная реализация === */

/* === Рекурсивная реализация === */

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

    return 1 + maximum(leftHeight, rightHeight);
}