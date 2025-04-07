#include "insert_sorting_str.h"
#include <string.h>
#include <stdlib.h>

int sorting_step(deque_str* deque) {
    if (dstr_is_empty(deque)) 
        return 0;

    char* current = dstr_pop_front(deque);

    if (dstr_is_empty(deque)) {
        dstr_push_back(deque, current);
        return 0;
    }

    deque_str* temp_storage = dstr_create(10);
    if (!temp_storage) {
        dstr_push_front(deque, current);
        return 0;
    }

    char* next = dstr_pop_front(deque);

    while (strcmp(next, current) >= 0) {
        dstr_push_back(temp_storage, current);
        current = next;

        if (dstr_is_empty(deque)) {
            dstr_push_back(temp_storage, current);

            while (!dstr_is_empty(temp_storage))
                dstr_push_back(deque, dstr_pop_front(temp_storage));
            
            dstr_destroy(temp_storage);
            return 0;
        }

        next = dstr_pop_front(deque);
    }

    dstr_push_back(temp_storage, current);

    while (!dstr_is_empty(deque)) 
        dstr_push_back(temp_storage, dstr_pop_front(deque));


    int inserted = 0;

    while (!dstr_is_empty(temp_storage)) {
        current = dstr_pop_front(temp_storage);

        if (!inserted && strcmp(current, next) > 0) {
            dstr_push_back(deque, next);
            inserted = 1;
        }
        dstr_push_back(deque, current);
    }

    if (!inserted) 
        dstr_push_back(deque, next);

    dstr_destroy(temp_storage);
    return 1;
}

void insert_sort(deque_str* deque) {
    while (sorting_step(deque));
}