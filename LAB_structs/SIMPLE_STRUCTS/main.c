#include <stdio.h>
#include <string.h>
#include "structs.h"

void test_static_stack(int ex) {

    printf("\nTesting static stack...\n\n");
    stack* st = create_stack(3);
    
    printf("    Max Len = 3\n    Pushing elements: 1.1, 2.2, 3.3\n\n");
    push_back_stack(st, 1.1);
    push_back_stack(st, 2.2);
    push_back_stack(st, 3.3);

    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to push back the 4th element:\n    ");
        push_back_stack(st, 3.4); 
    }

    printf("    Popping elements: %.1f %.1f %.1f\n\n", 
        pop_back_stack(st), pop_back_stack(st), pop_back_stack(st));


    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to pop back an element from the empty stack:\n    ");
        pop_back_stack(st);
    }
    
    destroy_stack(st);

}

void test_static_queue(int ex) {

    printf("\nTesting static queue...\n\n");
    queue* qu = create_queue(3);
    
    printf("    Max Len = 3\n    Pushing elements: 1.1, 2.2, 3.3\n\n");
    
    push_back_queue(qu, 1.1);
    push_back_queue(qu, 2.2);
    push_back_queue(qu, 3.3);

    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to push back the 4th element:\n    ");
        push_back_queue(qu, 3.4);
    }

    printf("    Popping one element: %.1f\n\n", pop_front_queue(qu));

    printf("    Current len = 2\n    Pushing element: 5.1\n\n");

    push_back_queue(qu, 5.1);

    printf("    Popping elements: %.1f %.1f %.1f\n\n", 
        pop_front_queue(qu), pop_front_queue(qu), pop_front_queue(qu));
    
    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to pop front an element from the empty queue:\n    ");
        pop_front_queue(qu);
    }

    destroy_queue(qu);

}

void test_static_deque(int ex) {

    printf("\nTesting static deque...\n\n");
    deque* deq = create_deque(3);
    
    printf("    Max Len = 3\n    Pushing elements to front: 1.1, 2.2, 3.3\n\n");

    push_front_deque(deq, 1.1);
    push_front_deque(deq, 2.2);
    push_back_deque(deq, 3.3);

    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to push back the 4th element:\n    ");
        push_back_deque(deq, 3.4);
        printf("    Trying to push front the 4th element:\n    ");
        push_front_deque(deq, 3.5);
    } 
    
    printf("    Popping elements from back: %.1f %.1f %.1f\n\n", 
        pop_back_deque(deq), pop_back_deque(deq), pop_back_deque(deq));
    
    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to pop back an element from the empty deque:\n    ");
        pop_back_deque(deq);
    }
  
    destroy_deque(deq);

}

void test_dyn_stack(int ex) {
    
    printf("\nTesting dynamic stack...\n\n");
    dyn_stack* dst = create_dyn_stack();
    
    printf("    Pushing elements: 4.4, 5.5, 6.6, 7.7\n\n");
    push_back_dyn_stack(dst, 4.4);
    push_back_dyn_stack(dst, 5.5);
    push_back_dyn_stack(dst, 6.6);
    push_back_dyn_stack(dst, 7.7);
    
    printf("    Popping elements: %.1f %.1f %.1f %.1f\n\n", 
        pop_back_dyn_stack(dst), pop_back_dyn_stack(dst), 
        pop_back_dyn_stack(dst), pop_back_dyn_stack(dst));
    
    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to pop back an element from the empty stack:\n    ");
        pop_back_dyn_stack(dst); 
    }
 
    destroy_dyn_stack(dst);

}

void test_dyn_queue(int ex) {

    printf("\nTesting dynamic queue...\n\n");
    dyn_queue* dqu = create_dyn_queue();
    
    printf("    Pushing elements: 4.4, 5.5, 6.6, 7.7\n\n");
    push_back_dyn_queue(dqu, 4.4);
    push_back_dyn_queue(dqu, 5.5);
    push_back_dyn_queue(dqu, 6.6);
    push_back_dyn_queue(dqu, 7.7);

    
    printf("    Popping elements: %.1f %.1f %.1f %.1f\n\n", 
        pop_front_dyn_queue(dqu), pop_front_dyn_queue(dqu), 
        pop_front_dyn_queue(dqu), pop_front_dyn_queue(dqu));

    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to pop back an element from the empty queue:\n    ");
        pop_front_dyn_queue(dqu);
    } 
    
    destroy_dyn_queue(dqu);

}

void test_dyn_deque(int ex) {

    printf("\nTesting dynamic deque...\n\n");
    dyn_deque* ddeq = create_dyn_deque();
    
    printf("    Pushing elements to back: 7.7, 9.9, 0.2\n");
    push_back_dyn_deque(ddeq, 7.7);
    push_back_dyn_deque(ddeq, 9.9);
    push_back_dyn_deque(ddeq, 0.2);
    
    
    printf("    Pushing elements to front: 8.8, 100.1\n\n");
    push_front_dyn_deque(ddeq, 8.8);
    push_front_dyn_deque(ddeq, 100.1);

    printf("    Popping elements from front: %.1f %.1f %.1f\n", 
        pop_front_dyn_deque(ddeq), pop_front_dyn_deque(ddeq), 
        pop_front_dyn_deque(ddeq));

    printf("    Popping elements from back: %.1f %.1f\n\n", 
        pop_back_dyn_deque(ddeq), pop_back_dyn_deque(ddeq));

    if (ex == 1) { // EXCEPTION KEY
        printf("    Trying to pop back an element from the empty deque:\n    ");
        pop_front_dyn_deque(ddeq);
    }

    destroy_dyn_deque(ddeq);
}

int main(int argc, char* argv[]) {

    if (argc == 1) { // WITHOUT ANY KEYS (all)

        test_static_stack(0);
        test_static_queue(0);
        test_static_deque(0);
        test_dyn_stack(0);
        test_dyn_queue(0);
        test_dyn_deque(0);

    } else if (argc == 2) { // ONLY ONE KEY (-s or -d)

        char key[10];
        strcpy(key, argv[1]);

        if (!strcmp(key, "-s")) { // ONLY STATIC STRUCTS (-s)
       
            test_static_stack(0);
            test_static_queue(0);
            test_static_deque(0);
       
        } else if (!strcmp(key, "-d")) { // ONLY DYNAMIC STRUCTS (-d)

            test_dyn_stack(0);
            test_dyn_queue(0);
            test_dyn_deque(0);

        } else { // ONLY EXEPTIONS
        
            if (!strcmp(key, "-Ess"))  
                test_static_stack(1);

            else if (!strcmp(key, "-Esq"))
                test_static_queue(1);

            else if (!strcmp(key, "-Esd"))
                test_static_deque(1);
            
            else if (!strcmp(key, "-Eds"))
                test_dyn_stack(1);

            else if (!strcmp(key, "-Edq"))
                test_dyn_queue(1);

            else if (!strcmp(key, "-Edd"))
                test_dyn_deque(1);
        }

    } else if (argc == 3) { // TWO KEYS (maximum)

        char key1[10];
        char key2[10];

        strcpy(key1, argv[1]);
        strcpy(key2, argv[2]);

        if (!strcmp(key1, "-s")) { // TYPES OF STATIC STRUCTS
            
            if (!strcmp(key2, "stack"))
                test_static_stack(0);

            else if (!strcmp(key2, "queue"))
                test_static_queue(0);

            else if (!strcmp(key2, "deque"))
                test_static_deque(0);

        } else if (!strcmp(key1, "-d")) { // TYPES OF DYNAMIC STRUCTS

            if (!strcmp(key2, "stack"))
                test_dyn_stack(0);

            else if (!strcmp(key2, "queue"))
                test_dyn_queue(0);

            else if (!strcmp(key2, "deque"))
                test_dyn_deque(0);

        }

    } else 
        fprintf(stderr, "Too many arguments\n");

}
