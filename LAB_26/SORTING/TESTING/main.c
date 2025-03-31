#include "../../../LAB_structs/DIFFICULT_STRUCTS/dbl/deque_dbl.h"
#include "../INSERT_SORT/insert_sort.h"
#include <stdio.h>

// Simple sorting test
static void test_sort() {
    printf("=== Sorting test ===\n");
    
    deque_dbl* deq = ddbl_create(10);
    
    // Add elements in random order
    ddbl_push_back(deq, 3.2);
    ddbl_push_back(deq, 1.1);
    ddbl_push_front(deq, 5.4);
    ddbl_push_back(deq, 2.3);
    ddbl_push_front(deq, 4.5);
    
    // Print before sorting
    printf("Before: ");
    for (int i = 0; i < deq->len; i++) {
        double val = ddbl_pop_front(deq);
        printf("%.1f ", val);
        ddbl_push_back(deq, val);
    }
    printf("\n");
    
    // Sort the deque
    insert_sort(deq);
    
    // Print after sorting
    printf("After:  ");
    for (int i = 0; i < deq->len; i++) {
        double val = ddbl_pop_front(deq);
        printf("%.1f ", val);
        ddbl_push_back(deq, val);
    }
    printf("\n");
    
    // Verify sorting
    int is_sorted = 1;
    double prev = ddbl_pop_front(deq);
    ddbl_push_back(deq, prev);
    
    for (int i = 1; i < deq->len; i++) {
        double current = ddbl_pop_front(deq);
        ddbl_push_back(deq, current);
        if (current < prev) {
            is_sorted = 0;
            break;
        }
        prev = current;
    }
    
    printf("Status: %s\n\n", is_sorted ? "PASSED" : "FAILED");
    ddbl_destroy(deq);
}

// Empty deque test
static void test_empty() {
    printf("=== Empty deque test ===\n");
    deque_dbl* deq = ddbl_create(5);
    insert_sort(deq);
    
    printf("Status: %s\n\n", ddbl_is_empty(deq) ? "PASSED" : "FAILED");
    ddbl_destroy(deq);
}

// Single element test
static void test_single() {
    printf("=== Single element test ===\n");
    deque_dbl* deq = ddbl_create(5);
    ddbl_push_back(deq, 42.0);
    insert_sort(deq);
    
    int status = (deq->len == 1) && (ddbl_pop_front(deq) == 42.0);
    printf("Status: %s\n\n", status ? "PASSED" : "FAILED");
    ddbl_destroy(deq);
}

int main() {
    test_empty();
    test_single();
    test_sort();
    
    return 0;
}