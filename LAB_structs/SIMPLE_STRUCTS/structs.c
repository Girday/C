#include "structs.h"
#include <stdio.h>


    /* STATIC */

// === static_stack ===

stack* create_stack(int max_len) {

    stack* res = malloc(sizeof(stack));

    if (res == NULL) {
        fprintf(stderr, "Creating stack is failed\n\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(double) * max_len);

    if (res -> buf == NULL) {

        fprintf(stderr, "Creating stack is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> max_len = max_len;

    return res;

}

void destroy_stack(stack* st) {
    
    free(st -> buf);
    free(st);

}

int is_empty_stack(stack* st) {
    return st -> len == 0;
}

int push_back_stack(stack* st, double element) {

    if (st -> len == st -> max_len) {
        fprintf(stderr, "Stack is full\n\n");
        return 0;
    }

    st -> buf[st -> len] = element;
    st -> len++;

    return 1;

}

double pop_back_stack(stack* st) {

    if (is_empty_stack(st)) {
        fprintf(stderr, "Stack is empty\n\n");
        exit(-1);
    }

    return st -> buf[--st -> len];;

}


// === static_queqe ===

queue* create_queue(int max_len) {

    queue* res = malloc(sizeof(queue));

    if (res == NULL) {
        fprintf(stderr, "Creating queue is failed\n\n");        
        return NULL;
    }

    res -> buf = malloc(sizeof(double) * max_len);

    if (res -> buf == NULL) {

        fprintf(stderr, "Creating queue is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;

}

void destroy_queue(queue* qu) {

    free(qu -> buf);
    free(qu);

}

int is_empty_queue(queue* qu) {
    return qu -> len == 0;
}

int push_back_queue(queue* qu, double element) {

    if (qu -> len == qu -> max_len) {
        fprintf(stderr, "Queue is full\n\n");
        return 0;
    }

    qu -> buf[(qu -> start + qu -> len) % qu -> max_len] = element;
    qu -> len++;

    return 1;

}

double pop_front_queue(queue* qu) {

    if (qu -> len == 0) {
        fprintf(stderr, "Queue is empty\n\n");
        exit(-1);
    }

    double elem = qu -> buf[qu -> start];

    qu -> start = (qu -> start + 1) % qu -> max_len;
    qu -> len--;

    return elem;

}


// === static_deque ===

deque* create_deque(int max_len) {

    deque* res = malloc(sizeof(deque));

    if (res == NULL) {
        fprintf(stderr, "Creating deque is failed\n\n");
        return NULL;
    }

    res -> buf = malloc(sizeof(double) * max_len);

    if (res -> buf == NULL) {
        
        fprintf(stderr, "Creating deque is failed\n\n");
        free(res);
        return NULL;

    }

    res -> len = 0;
    res -> start = 0;
    res -> max_len = max_len;

    return res;

}

void destroy_deque(deque* deq) {
    free(deq -> buf);
    free(deq);
}

int is_empty_deque(deque* deq) {
    return deq -> len == 0;
}

int push_back_deque(deque* deq, double element) {

    if (deq -> len == deq -> max_len) {
        fprintf(stderr, "Deque is full\n\n");
        return 0;
    }

    deq -> buf[(deq -> start + deq -> len) % deq -> max_len] = element;
    deq -> len++;

    return 1;

}

int push_front_deque(deque* deq, double element) {

    if (deq -> len == deq -> max_len) {
        fprintf(stderr, "Deque is full\n\n");
        return 0;
    }

    deq -> start = (deq -> start - 1 + deq -> max_len) % deq -> max_len;
    deq -> buf[deq -> start] = element;
    deq -> len++;

    return 1;
    
}

double pop_back_deque(deque* deq) {

    if (deq -> len == 0) {
        fprintf(stderr, "Deque is empty\n\n");
        exit(-1);
    }

    double elem = deq -> buf[(deq -> start + deq -> len - 1) % deq -> max_len];
    deq -> len--;

    return elem;

}

double pop_front_deque(deque* deq) {

    if (deq -> len == 0) {
        fprintf(stderr, "Deque is empty\n\n");
        exit(-1);
    }

    double elem = deq -> buf[deq -> start];
    deq -> start = (deq -> start + 1) % deq -> max_len;
    deq -> len--;

    return elem;

}


    /* LINKED LISTS */

// === stack by LL ===

dyn_stack* create_dyn_stack() {

    dyn_stack* res = malloc(sizeof(dyn_stack));

    if (res == NULL) {
        fprintf(stderr, "Creating dynamic stack is failed\n\n");
        return NULL;
    }

    res -> first = NULL;

    return res;

}

void destroy_dyn_stack(dyn_stack* dst) {

    elem* cur = dst -> first;

    while (cur != NULL) {

        elem* next = dst -> first;
        free(cur);
        cur = next;

    }

    free(dst);

}

int is_empty_dyn_stack(dyn_stack* dst) {
    return dst -> first == NULL;
}

int push_back_dyn_stack(dyn_stack* dst, double element) {

    elem* new = malloc(sizeof(elem));

    if (new == NULL) {
        fprintf(stderr, "Adding a new element to the dynamic stack is failed\n\n");
        return 0;
    }

    new -> value = element;
    new -> next = dst -> first;
    dst -> first = new;

    return 1;

}

double pop_back_dyn_stack(dyn_stack* dst) {

    if (is_empty_dyn_stack(dst)) {
        fprintf(stderr, "Dynamic stack is empty\n\n");
        exit(-1);
    }

    double element = dst -> first -> value;
    elem* next = dst -> first -> next;

    free(dst -> first);

    dst -> first = next;

    return element;

}


// === queue by LL ===

dyn_queue* create_dyn_queue() {

    dyn_queue* res = malloc(sizeof(dyn_queue));

    if (res == NULL) {
        fprintf(stderr, "Creating dynamic queue is failed\n\n");
        return NULL;
    }

    res -> first = NULL;
    res -> last = NULL;

    return res;

}

void destroy_dyn_queue(dyn_queue* dqu) {

    elem* cur = dqu -> first;

    while (cur != NULL) {

        elem* next = cur -> next;
        free(cur);
        cur = next;

    }

    free(dqu);

}

int is_empty_dyn_queue(dyn_queue* dqu) {
    return dqu -> first == NULL; 
}

int push_back_dyn_queue(dyn_queue* dqu, double element) {

    elem* new = malloc(sizeof(elem));

    if (new == NULL) {
        fprintf(stderr, "Adding a new element to the dynamic queue is failed\n\n");
        return 0;
    }

    new -> value = element;
    new -> next = NULL;

    if (dqu -> last == NULL) {
        dqu -> last = dqu -> first = new;
    } else {
        dqu -> last -> next = new;
        dqu -> last = new;
    }

    return 1;

}

double pop_front_dyn_queue(dyn_queue* dqu) {

    if (is_empty_dyn_queue(dqu)) {
        fprintf(stderr, "Dynamic queue is empty\n\n");
        exit(-1);
    }

    elem* new_first = dqu -> first -> next;

    double element = dqu -> first -> value;
    
    
    free(dqu -> first);
    dqu -> first = new_first;

    if (dqu -> first == NULL) {
        dqu -> last = NULL;
    }

    return element;

}


// === deque by LL ===

dyn_deque* create_dyn_deque() {

    dyn_deque* res = malloc(sizeof(dyn_deque));

    if (res == NULL) {
        fprintf(stderr, "Creating dynamic deque is failed\n\n");
        return NULL;
    }

    res -> first = NULL;
    res -> last = NULL;

    return res;

}

void destroy_dyn_deque(dyn_deque* ddeq) {

    elem* cur = ddeq -> first;

    while (cur != NULL) {

        elem* next = cur -> next;
        free(cur);
        cur = next;

    }

    free(ddeq);

}

int is_empty_dyn_deque(dyn_deque* ddeq) {
    return ddeq -> first == NULL;
}

int push_back_dyn_deque(dyn_deque* ddeq, double element) {

    elem* new = malloc(sizeof(elem));

    if (new == NULL) {
        fprintf(stderr, "Adding a new element to the back of the dynamic deque is failed\n\n");
        return 0;
    }

    new -> value = element;
    new -> next = NULL;
    new -> prev = ddeq -> last;

    if (ddeq -> last == NULL) {
        ddeq -> last = ddeq -> first = new;
    } else {
        ddeq -> last -> next = new;
        ddeq -> last = new;
    }

    return 1;

}

int push_front_dyn_deque(dyn_deque* ddeq, double element) {

    elem* new = malloc(sizeof(elem));

    if (new == NULL) {
        fprintf(stderr, "Adding a new element to the front of the dynamic deque is failed\n\n");
        return 0;
    }

    new -> value = element;
    new -> next = ddeq -> first;
    new -> prev = NULL;

    if (ddeq -> first == NULL) {
        ddeq -> first = ddeq -> last = new;
    } else {
        ddeq -> first -> prev = new;
        ddeq -> first = new;
    }

    return 1;
        
}

double pop_back_dyn_deque(dyn_deque* ddeq) {

    if (is_empty_dyn_deque(ddeq)) {
        fprintf(stderr, "Dynamic deque is empty\n\n");
        exit(-1);
    }

    elem* new_last = ddeq -> last -> prev;

    double element = ddeq -> last -> value;
    
    free(ddeq -> last);
    ddeq -> last = new_last;

    if (ddeq -> last == NULL) {
        ddeq -> first = NULL;
    } else {
        ddeq -> last -> next = NULL;
    }

    return element;

}

double pop_front_dyn_deque(dyn_deque* ddeq) {

    if (is_empty_dyn_deque(ddeq)) {
        fprintf(stderr, "Dynamic deque is empty\n\n");
        exit(-1);
    }

    elem* new_first = ddeq -> first -> next;

    double element = ddeq -> first -> value;

    free(ddeq -> first);
    ddeq -> first = new_first;

    if (ddeq -> first == NULL) {
        ddeq -> first = ddeq -> last = NULL;
    } else {
        ddeq -> first -> prev = NULL;
    }

    return element;

}
