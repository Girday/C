#include "../../../LAB_structs/DIFFICULT_STRUCTS/dbl/deque_dbl.h"
#include "insert_sort.h"
#include <stdio.h>

int step_of_a_sort(deque_dbl* ddbl) {
    if (ddbl_is_empty(ddbl))
        return 0;
    
    double e1 = ddbl_pop_front(ddbl);

    if (ddbl_is_empty(ddbl)) {
        ddbl_push_front(ddbl, e1);
        return 0;
    }
    
    deque_dbl* temp = ddbl_create(ddbl -> max_len + 1);
    double e2 = ddbl_pop_front(ddbl);
    
    while (e2 >= e1) {
        ddbl_push_back(temp, e1);
        e1 = e2;

        if (ddbl_is_empty(ddbl)) {
            ddbl_push_back(temp, e1);

            while (!ddbl_is_empty(temp))
                ddbl_push_back(ddbl, ddbl_pop_front(temp));

            ddbl_destroy(temp);

            return 0;
        }

        e2 = ddbl_pop_front(ddbl);
    }

    ddbl_push_back(temp, e1);
    
    while (!ddbl_is_empty(ddbl))
        ddbl_push_back(temp, ddbl_pop_front(ddbl));
    
    int inserted = 0;
    deque_dbl* result = ddbl_create(temp -> max_len);

    while (!ddbl_is_empty(temp)) {
        double x = ddbl_pop_front(temp);

        if (!inserted && e2 < x) {
            ddbl_push_back(result, e2);
            inserted = 1;
        }

        ddbl_push_back(result, x);
    }

    if (!inserted)
        ddbl_push_back(result, e2);
    
    while (!ddbl_is_empty(result))
        ddbl_push_back(ddbl, ddbl_pop_front(result));
    
    ddbl_destroy(result);
    ddbl_destroy(temp);

    return 1;
}

void insert_sort(deque_dbl* ddbl) {
    while (step_of_a_sort(ddbl));
}
