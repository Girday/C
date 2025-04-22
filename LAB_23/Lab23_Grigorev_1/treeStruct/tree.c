#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

#include "../queueOnTree/queue_tree.h"
#include "../stackOnTree/stack_tree.h"
#include "../stackOnInt/stack_int.h"


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
    if (isEmpty(t)) {
        printf("Error: Attempt to get value from NULL node.\n");
        return 0.0;
    }
    
    return t -> val;
}

tree getLeft(tree t) {
    if (isEmpty(t)) {
        printf("Error: Attempt to get left child from NULL node.\n");
        return NULL;
    }

    return t -> left;
}

tree getRight(tree t) {
    if (isEmpty(t)) {
        printf("Error: Attempt to get right child from NULL node.\n");
        return NULL;
    }

    return t -> right;
}

tree build(double val, tree left, tree right) {
    tree res = malloc(sizeof(treeNode));

    if (isEmpty(res))
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

void setValue(tree t, double val) {
    if (isEmpty(t)) {
        printf("Error: Attempt to set value on NULL node.\n");
        return;
    }

    t -> val = val;
}

void setLeft(tree t, tree left) {
    if (isEmpty(t)) {
        printf("Error: Attempt to set left on NULL node.\n");
        return;
    }

    t -> left = left;
}

void setRight(tree t, tree right) {
    if (isEmpty(t)) {
        printf("Error: Attempt to set right on NULL node.\n");
        return;
    }

    t -> right = right;
}

tree* getLeftPtr(tree t) {
    if (isEmpty(t)) {
        printf("Error: Attempt to get left pointer from NULL node.\n");
        return NULL;
    }

    return &(t -> left);
}

tree* getRightPtr(tree t) {
    if (isEmpty(t)) {
        printf("Error: Attempt to get right pointer from NULL node.\n");
        return NULL;
    }

    return &(t -> right);
}


                        /* === УНИЧТОЖЕНИЕ ВСЕГО ДЕРЕВА === */

/* === Итеративная реализация === */

void destroyTree(tree t) {
    if (isEmpty(t))
        return;
    
    stack_tree* stree = stree_create(10);
    stree_push(stree, t);
    
    while (!stree_is_empty(stree)) {
        tree cur = stree_pop(stree);
        
        if (!isEmpty(getRight(cur)))
            stree_push(stree, getRight(cur));
        
        if (!isEmpty(getLeft(cur)))
            stree_push(stree, getLeft(cur));
        
        destroy(cur);
    }
    
    stree_destroy(stree);
}


/* === Рекурсивная реализация === */

// void destroyTree(tree t) {
//     if (isEmpty(t))
//         return;

//     destroyTree(getLeft(t));
//     destroyTree(getRight(t));

//     destroy(t);
// }


                        /* === ДОБАВЛЕНИЕ УЗЛА === */

/* === Итеративная реализация === */

int addNode(tree *t, double val) {
    tree* cur = t;

    while (!isEmpty(*cur)) {
        if (val < getValue(*cur))
            cur = getLeftPtr(*cur);
        else if (val > getValue(*cur))
            cur = getRightPtr(*cur);
        else
            return 0;
    }
    
    *cur = malloc(sizeof(treeNode));
    
    if (isEmpty(*cur)) {
        printf("Error: Can't add a node (allocation error)\n");
        return -1;
    }
    
    setValue(*cur, val);
    setLeft(*cur, NULL);
    setRight(*cur, NULL);
    
    return 1;
}

/*   === Рекурсивная реализация ===   */

// int addNode(tree *t, double val) {
//     if (*t == NULL) {
//         *t = malloc(sizeof(treeNode));

//         if (*t == NULL) { 
//             printf("Error: Can't add a node (allocation error)\n");
//             return 0;
//         }

//         (*t) -> val = val;
//         (*t) -> left = NULL;
//         (*t) -> right = NULL;

//         return 1;
//     }

//     if (val < (*t) -> val) 
//         return addNode(&(*t) -> left, val);
    
//     if (val > (*t) -> val)
//         return addNode(&(*t) -> right, val);

//     return 0;
// }


                        /* === УДАЛЕНИЕ УЗЛА === */

/* === Итеративная реализация === */

tree removeNode(tree t, double val) {
    tree cur = t;
    tree parent = NULL;
    
    while (!isEmpty(cur) && getValue(cur) != val) {
        parent = cur;
        cur = (val < getValue(cur)) ? getLeft(cur) : getRight(cur);
    }
    
    if (isEmpty(cur)) 
        return t;
    
    if (isEmpty(getLeft(cur)) || isEmpty(getRight(cur))) {
        tree child = (!isEmpty(getLeft(cur))) ? getLeft(cur) : getRight(cur);
        
        if (isEmpty(parent)) {
            free(cur);
            return child;
        }
        
        if (getLeft(parent) == cur) 
            setLeft(parent, child);
        else 
            setRight(parent, child);
        
        destroy(cur);
    }

    else {
        tree successor = getRight(cur);
        tree successorParent = cur;
        
        while (!isEmpty(getLeft(successor))) {
            successorParent = successor;
            successor = getLeft(successor);
        }
        
        setValue(cur, getValue(successor));
        
        if (getLeft(successorParent) == successor) 
            setLeft(successorParent, getRight(successor));
        else 
            setRight(successorParent, getRight(successor));
        
        destroy(successor);
    }
    
    return t;
}


/*   === Рекурсивная реализация ===   */

// tree removeNode(tree t, double val) {
//     if (isEmpty(t))
//         return t;
    
//     if (val < getValue(t)) {
//         tree left = removeNode(getLeft(t), val);
//         tree res = build(getValue(t), left, getRight(t));
        
//         destroy(t);
        
//         return res;
//     } 

//     else if (val > getValue(t)) {
//         tree right = removeNode(getRight(t), val);
//         tree res = build(getValue(t), getLeft(t), right);
        
//         destroy(t);
        
//         return res;
//     }
    
//     if (isEmpty(getLeft(t))) {
//         tree res = getRight(t);
//         destroy(t);
        
//         return res;
//     } 

//     else if (isEmpty(getRight(t))) {
//         tree res = getLeft(t);
//         destroy(t);
        
//         return res;
//     }
    
//     tree maxLeft = getLeft(t);

//     while (!isEmpty(getRight(maxLeft)))
//         maxLeft = getRight(maxLeft);
    
//     double maxLeftVal = getValue(maxLeft);
    
//     tree left = removeNode(getLeft(t), maxLeftVal);
//     tree res = build(maxLeftVal, left, getRight(t));
    
//     destroy(t);

//     return res;
// }


                        /* === ГЛУБИНА ДЕРЕВА === */

/* === Итеративная реализация === */

int getDepth(tree t) {
    if (isEmpty(t)) 
        return 0;

    stack_tree* nodes = stree_create(10);
    stack_int* depths = sint_create(10);
    
    stree_push(nodes, t);
    sint_push(depths, 1);
    
    int max = 0;

    while (!stree_is_empty(nodes)) {
        tree n = stree_pop(nodes);
        int d = sint_pop(depths);
        
        max = maximum(d, max);
        
        if (!isEmpty(getRight(n))) {
            stree_push(nodes, getRight(n));
            sint_push(depths, d + 1);
        }

        if (!isEmpty(getLeft(n))) {
            stree_push(nodes, getLeft(n));
            sint_push(depths, d + 1);
        }
    }

    stree_destroy(nodes);
    sint_destroy(depths);
    
    return max;
}

/* === Рекурсивная реализация === */

// int getDepth(tree t) {
//     if (t == NULL)
//         return 0;
    
//     return 1 + maximum(getDepth(getLeft(t)), getDepth(getRight(t)));
// }


                        /* === ОПРЕДЕЛЕНИЕ УРОВНЯ === */

int getLevel(tree t, double val) {
    int level = 0;
    tree cur = t;

    while (!isEmpty(cur)) {
        if (val == getValue(cur))
            return level;
        else if (val < getValue(cur))
            cur = getLeft(cur);
        else 
            cur = getRight(cur);
        
        level++;
    }

    return -1;
}

                        /* === ШИРИНА КОНКРЕТНОГО УРОВНЯ === */

/* === Итеративная реализация === */

int levelWidth(tree t, int k) {
    if (isEmpty(t)) 
        return 0;

    if (k == 0) 
        return 1;

    queue_tree* q = qtree_create(10);
    qtree_push(q, t);

    int curDepth = 0;
    int width = 0;

    while (!qtree_is_empty(q) && curDepth < k) {
        int levelSize = qtree_get_size(q);
        
        for (int i = 0; i < levelSize; i++) {
            tree node = qtree_pop(q);
            
            if (!isEmpty(getLeft(node)))
                qtree_push(q, getLeft(node));

            if (!isEmpty(getRight(node)))
                qtree_push(q, getRight(node));
        }
        
        curDepth++;
    }

    if (curDepth == k)
        width = qtree_get_size(q);

    qtree_destroy(q);

    return width;
}

/* === Рекурсивная реализация === */

// int levelWidth(tree t, int k) {
//     if (k == 0) {
//         if (t != NULL)
//             return 1;
    
//         return 0;
//     }

//     return levelWidth(getLeft(t), k - 1) + levelWidth(getRight(t), k - 1);
// }


                        /* === ШИРИНА ДЕРЕВА === */

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

int checkAVL(tree t) {
    if (isEmpty(t)) 
        return 1;

    stack_tree* nodes = stree_create(10);
    stack_int* min_stack = sint_create(10);
    stack_int* max_stack = sint_create(10);
    stack_int* state_stack = sint_create(10);

    stree_push(nodes, t);
    sint_push(min_stack, INT_MIN);
    sint_push(max_stack, INT_MAX);
    sint_push(state_stack, 0);

    int is_avl = 1;

    while (!stree_is_empty(nodes) && is_avl) {
        tree node = stree_top(nodes);
        int state = sint_top(state_stack);
        double min_val = sint_top(min_stack);
        double max_val = sint_top(max_stack);

        if (getValue(node) <= min_val || getValue(node) >= max_val) {
            is_avl = 0;
            break;
        }

        if (state == 0) {
            sint_pop(state_stack);
            sint_push(state_stack, 1);

            if (!isEmpty(getLeft(node))) {
                stree_push(nodes, getLeft(node));
                sint_push(min_stack, min_val);
                sint_push(max_stack, getValue(node));
                sint_push(state_stack, 0);
            }
        } 
        
        else if (state == 1) {
            sint_pop(state_stack);
            sint_push(state_stack, 2);

            if (!isEmpty(getRight(node))) {
                stree_push(nodes, getRight(node));
                sint_push(min_stack, getValue(node));
                sint_push(max_stack, max_val);
                sint_push(state_stack, 0);
            }
        } 
        
        else {
            stree_pop(nodes);
            sint_pop(min_stack);
            sint_pop(max_stack);
            sint_pop(state_stack);

            int left_height = getDepth(getLeft(node));
            int right_height = getDepth(getRight(node));

            if (abs(left_height - right_height) > 1)
                is_avl = 0;
        }
    }

    stree_destroy(nodes);
    sint_destroy(min_stack);
    sint_destroy(max_stack);
    sint_destroy(state_stack);

    return is_avl;
}
