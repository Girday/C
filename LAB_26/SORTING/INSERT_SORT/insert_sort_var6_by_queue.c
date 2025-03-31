#include "insert_sort.h"
#include "../../../LAB_structs/DIFFICULT_STRUCTS/dbl/queue_dbl.h"

int step_of_a_sort(queue_dbl* q) {
    if (qdbl_is_empty(q))
        return 0;

    double e1 = qdbl_pop(q);

    if (qdbl_is_empty(q)) {
        qdbl_push(q, e1);
        return 0;
    }

    queue_dbl* storage = qdbl_create(10);
    double e2 = qdbl_pop(q);

    while (e2 >= e1) {
        qdbl_push(storage, e1);
    
        e1 = e2;

        if (qdbl_is_empty(q)) {
            qdbl_push(storage, e1);

            while (!qdbl_is_empty(storage))
                qdbl_push(q, qdbl_pop(storage));

            return 0;
        }

        e2 = qdbl_pop(q);
    }

    qdbl_push(storage, e1);
    while (!qdbl_is_empty(q))
        qdbl_push(storage, qdbl_pop(q));

    int was_added = 0;

    while (!qdbl_is_empty(storage)) {
        e1 = qdbl_pop(storage);

        if (e1 <= e2) 
            qdbl_push(q, e1);

        else if (!was_added) {
            qdbl_push(q, e2);
            was_added = 1;
        }
    }

    if (!was_added) 
        qdbl_push(q, e2);
    
    return 1;
}

void insert_sort(queue_dbl* q) {
    while (step_of_a_sort(q));
}
