#include "insert_sorting_str.h"
#include <string.h>
#include <stdlib.h>

int sorting_step(deque_str* dstr) {
    if (dstr_is_empty(dstr)) 
        return 0;

    char* current = dstr_pop_front(dstr);

    if (dstr_is_empty(dstr)) {
        dstr_push_back(dstr, current);
        return 0;
    }

    deque_str* temp_storage = dstr_create(10);

    if (!temp_storage) {
        dstr_push_front(dstr, current);
        return 0;
    }

    char* next = dstr_pop_front(dstr);

    while (strcmp(next, current) >= 0) {
        dstr_push_back(temp_storage, current);
        current = next;

        if (dstr_is_empty(dstr)) {
            dstr_push_back(temp_storage, current);

            while (!dstr_is_empty(temp_storage))
                dstr_push_back(dstr, dstr_pop_front(temp_storage));
            
            dstr_destroy(temp_storage);
            return 0;
        }

        next = dstr_pop_front(dstr);
    }

    dstr_push_back(temp_storage, current);

    while (!dstr_is_empty(dstr)) 
        dstr_push_back(temp_storage, dstr_pop_front(dstr));


    int inserted = 0;

    while (!dstr_is_empty(temp_storage)) {
        current = dstr_pop_front(temp_storage);

        if (!inserted && strcmp(current, next) > 0) {
            dstr_push_back(dstr, next);
            inserted = 1;
        }

        dstr_push_back(dstr, current);
    }

    if (!inserted) 
        dstr_push_back(dstr, next);

    dstr_destroy(temp_storage);
    
    return 1;
}

void insert_sort(deque_str* dstr) {
    while (sorting_step(dstr));
}