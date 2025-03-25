#include "../LAB_structs/DIFFICULT_STRUCTS/dbl/stack_dbl.h"

double remove_max(stack_dbl* st) {
    stack_dbl* storage = sdbl_create(10);
    double cur_max = sdbl_pop_back(st);
    sdbl_push_back(storage, cur_max);
    while (!sdbl_is_empty(st)) {
        double cur = sdbl_pop_back(st);
        if (cur > cur_max) cur_max = cur;
        sdbl_push_back(storage, cur);
    }
    int was_removed = 0;
    while (!sdbl_is_empty(storage)) {
        double cur = sdbl_pop_back(storage);
        if (cur != cur_max || was_removed) {
            sdbl_push_back(st, cur);
            continue;
        }
        was_removed = 1;
    }
    sdbl_destroy(storage);
    return cur_max;
}

void select_sort(stack_dbl* st) {
    stack_dbl* sorted = create();
    while (!sdbl_is_empty(st)) sdbl_push_back(sorted, remove_max(st));
    while (!sdbl_is_empty(sorted)) sdbl_push_back(st, sdbl_pop(back(sorted)));
    sdbl_destroy(sorted);
}