#include <stdio.h>
#include <stdlib.h>
#include "list_dbl.h"

// LIST
list_dbl* ldbl_create() {
    list_dbl* res = malloc(sizeof(list_dbl));
    if (res == NULL) return NULL;
    res->first = NULL;
    res->last = NULL;
    return res;
}

void ldbl_destroy(list_dbl* l) {
    if (l == NULL) return;

    elem* current = l->first;
    while (current != NULL) {
        elem* next = current->next;
        free(current);
        current = next;
    }

    free(l);
}

// ITERATOR
iter ldbl_begin(list_dbl* l) {
    return (iter){.l = l, .prev = NULL};
}

iter ldbl_end(list_dbl* l) {
    return (iter){.l = l, .prev = l->last};
}

iter ldbl_iter_move_next(iter it) {
    if (it.l == NULL || it.l->first == NULL) return it;
    if (it.prev == NULL) it.prev = it.l->first;
    else if (it.prev->next != NULL) it.prev = it.prev->next;
    return it;
}

int ldbl_iter_equal(iter it1, iter it2) {
    return it1.l == it2.l && it1.prev == it2.prev;
}

double ldbl_iter_get(iter it) {
    if (it.l == NULL || it.l->first == NULL) {
        printf("Error: Attempted to get value from an empty list!\n");
        exit(EXIT_FAILURE);
    }
    if (it.prev == NULL) return it.l->first->val;
    if (it.prev->next == NULL) {
        printf("Error: Iterator out of bounds in ldbl_iter_get!\n");
        exit(EXIT_FAILURE);
    }
    return it.prev->next->val;
}

void ldbl_iter_set(iter it, double val) {
    if (it.l == NULL || it.l->first == NULL) {
        printf("Error: Attempted to set value in an empty list!\n");
        return;
    }
    if (it.prev == NULL) it.l->first->val = val;
    else if (it.prev->next != NULL) it.prev->next->val = val;
    else printf("Warning: Iterator out of bounds in ldbl_iter_set!\n");
}

void ldbl_iter_insert(iter it, double val) {
    elem* new_elem = malloc(sizeof(elem));
    if (new_elem == NULL) {
        printf("Error: Memory allocation failed in ldbl_iter_insert!\n");
        exit(EXIT_FAILURE);
    }
    new_elem->val = val;

    if (it.prev == NULL) {
        new_elem->next = it.l->first;
        it.l->first = new_elem;
        if (it.l->last == NULL) it.l->last = new_elem;
    } else {
        new_elem->next = it.prev->next;
        it.prev->next = new_elem;
        if (new_elem->next == NULL) it.l->last = new_elem;
    }
}

void ldbl_iter_remove(iter it) {
    if (it.l == NULL || it.l->first == NULL) {
        printf("Warning: Attempted to remove from an empty list!\n");
        return;
    }

    if (it.prev == NULL) {
        // Удаляем первый элемент
        elem* e = it.l->first;
        if (e == NULL) return;
        it.l->first = e->next;
        if (it.l->first == NULL) {
            it.l->last = NULL;  // Если список стал пустым, обнуляем last
        }
        free(e);
    } else {
        // Удаляем НЕ первый элемент
        elem* e = it.prev->next;
        if (e == NULL) {
            printf("Warning: Attempted to remove NULL element in ldbl_iter_remove!\n");
            return;
        }
        it.prev->next = e->next;
        // Если удаляем последний элемент, корректируем last
        if (e->next == NULL) it.l->last = it.prev;
        free(e);
    }
}
