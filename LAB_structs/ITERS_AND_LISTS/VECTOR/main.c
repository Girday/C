#include <stdio.h>
#include "absolut_dbl.h"

int main() {

    svector_dbl* a = svdbl_create(12);

    printf("Size: %d, Max size: %d\n", svdbl_get_size(a), a -> max_size);

    svdbl_push_back(a, 1.1);
    svdbl_push_back(a, 1.2);
    svdbl_push_back(a, 1.3);
    svdbl_push_back(a, 1.4);

    printf("Size: %d, Max size: %d\n", svdbl_get_size(a), a -> max_size);

    double v1, v2, v3, v4;

    v1 = svdbl_pop_back(a);
    v2 = svdbl_pop_back(a);
    v3 = svdbl_pop_back(a);
    v4 = svdbl_pop_back(a);

    printf("Elems: %.1f, %.1f, %.1f, %.1f\n", v1, v2, v3, v4);

    printf("Size: %d, Max size: %d\n", svdbl_get_size(a), a -> max_size);

}
