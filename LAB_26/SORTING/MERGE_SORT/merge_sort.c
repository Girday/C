#include "../LAB_structs/DIFFICULT_STRUCTS/dbl/stack_dbl.h"

int merge(stack_dbl* s1, stack_dbl* s2, stack_dbl* res) {

    if (!sdbl_is_empty(s1)) {

        double e1 = sdbl_peek(s1), e2 = sdbl_peek(s2);

        while (!sdbl_is_empty(s1) && !sdbl_is_empty(s2)) {

            if (e1 >= e2) {
                sdbl_push(res, e1);
                e1 = sdbl_pop(s1);
            } 
            
            else {
                sdbl_push(res, e2);
                e2 = sdbl_pop(s2);
            }
        }

        while (!sdbl_is_empty(s1))
            sdbl_push(res, sdbl_pop(s1));
        
        while (!sdbl_is_empty(s2))
            sdbl_push(res, sdbl_pop(s2));

    }

}
