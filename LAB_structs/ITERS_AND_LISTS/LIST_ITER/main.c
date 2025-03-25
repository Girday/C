#include <stdio.h>
#include <assert.h>
#include "list_dbl.h"

void test_create_destroy() {
    list_dbl* list = ldbl_create();
    assert(list != NULL);
    assert(list->first == NULL);
    assert(list->last == NULL);
    ldbl_destroy(list);
    printf("test_create_destroy passed!\n");
}

void test_insert() {
    list_dbl* list = ldbl_create();
    iter it = ldbl_begin(list);
    ldbl_iter_insert(it, 10.0);
    assert(list->first != NULL);
    assert(list->last != NULL);
    assert(list->first->val == 10.0);
    assert(list->last->val == 10.0);
    
    ldbl_iter_insert(it, 20.0);
    assert(list->first->val == 20.0);
    assert(list->first->next->val == 10.0);
    
    ldbl_destroy(list);
    printf("test_insert passed!\n");
}

void test_iterate() {
    list_dbl* list = ldbl_create();
    ldbl_iter_insert(ldbl_begin(list), 1.0);
    ldbl_iter_insert(ldbl_begin(list), 2.0);
    ldbl_iter_insert(ldbl_begin(list), 3.0);
    
    iter it = ldbl_begin(list);
    assert(ldbl_iter_get(it) == 3.0);
    it = ldbl_iter_move_next(it);
    assert(ldbl_iter_get(it) == 2.0);
    it = ldbl_iter_move_next(it);
    assert(ldbl_iter_get(it) == 1.0);
    
    ldbl_destroy(list);
    printf("test_iterate passed!\n");
}

void test_remove() {
    list_dbl* list = ldbl_create();
    iter it = ldbl_begin(list);
    ldbl_iter_insert(it, 10.0);
    ldbl_iter_insert(it, 20.0);
    ldbl_iter_insert(it, 30.0);
    
    it = ldbl_begin(list);
    ldbl_iter_remove(it);
    assert(list->first->val == 20.0);
    assert(list->last->val == 10.0);
    
    it = ldbl_iter_move_next(it);
    ldbl_iter_remove(it);
    assert(list->first->val == 20.0);
    assert(list->last->val == 20.0);
    
    ldbl_destroy(list);
    printf("test_remove passed!\n");
}

void test_edge_cases() {
    list_dbl* list = ldbl_create();
    iter it = ldbl_begin(list);

    printf("Testing removal from empty list...\n");
    ldbl_iter_remove(it);
    assert(list->first == NULL && list->last == NULL);

    printf("Testing inserting and removing one element...\n");
    ldbl_iter_insert(it, 42.0);
    assert(list->first->val == 42.0 && list->last->val == 42.0);
    ldbl_iter_remove(it);
    assert(list->first == NULL && list->last == NULL);

    printf("Testing inserting multiple elements...\n");
    ldbl_iter_insert(it, 1.0);
    ldbl_iter_insert(it, 2.0);
    ldbl_iter_insert(it, 3.0);

    printf("Testing removing all elements...\n");
    it = ldbl_begin(list);
    ldbl_iter_remove(it);
    ldbl_iter_remove(it);
    ldbl_iter_remove(it);
    assert(list->first == NULL && list->last == NULL);

    ldbl_destroy(list);
    printf("test_edge_cases passed!\n");
}


int main() {
    test_create_destroy();
    test_insert();
    test_iterate();
    test_remove();
    test_edge_cases();
    printf("All tests passed!\n");
    return 0;
}
