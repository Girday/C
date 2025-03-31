#include "insert_sort.h"
#include "../../../LAB_structs/DIFFICULT_STRUCTS/dbl/deque_dbl.h"

int step_of_a_sort(deque_dbl* deq) {
    if (ddbl_is_empty(deq))
        return 0;

    double e1 = ddbl_pop_front(deq);

    if (ddbl_is_empty(deq)) {
        ddbl_push_back(deq, e1);
        return 0;
    }

    deque_dbl* storage = ddbl_create(10);
    double e2 = ddbl_pop_front(deq);

    while (e2 >= e1) {
        ddbl_push_back(storage, e1);
        e1 = e2;

        if (ddbl_is_empty(deq)) {
            ddbl_push_back(storage, e1);
            
            while (!ddbl_is_empty(storage))
                ddbl_push_back(deq, ddbl_pop_front(storage));
            
            ddbl_destroy(storage);
            return 0;
        }

        e2 = ddbl_pop_front(deq);
    }

    ddbl_push_back(storage, e1);

    while (!ddbl_is_empty(deq))
        ddbl_push_back(storage, ddbl_pop_front(deq));

    int was_added = 0;
    while (!ddbl_is_empty(storage)) {
        e1 = ddbl_pop_front(storage);

        if (!was_added && e1 > e2) {
            ddbl_push_back(deq, e2);
            was_added = 1;
        }

        ddbl_push_back(deq, e1);
    }

    if (!was_added)
        ddbl_push_back(deq, e2);

    ddbl_destroy(storage);
    return 1;
}

void insert_sort(deque_dbl* deq) {
    while (step_of_a_sort(deq));
}
