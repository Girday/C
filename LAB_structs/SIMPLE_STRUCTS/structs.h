#pragma once
#include <stdlib.h>


    /* STATIC */

// === static_stack ===

typedef struct {
    double* buf;
    int len;
    int max_len;
} stack;

stack* create_stack(int max_len);
void destroy_stack(stack* st);
int is_empty_stack(stack* st);
int push_back_stack(stack* st, double element);
double pop_back_stack(stack* st);


// === static_queqe ===

typedef struct {
    double* buf;
    int len;
    int max_len;
    int start;
} queue;

queue* create_queue(int max_len);
void destroy_queue(queue* qu);
int is_empty_queue(queue* qu);
int push_back_queue(queue* qu, double element);
double pop_front_queue(queue* qu);


// === static_deque ===

typedef struct {
    double* buf;
    int len;
    int max_len;
    int start;
} deque;

deque* create_deque(int max_len);
void destroy_deque(deque* deq);
int is_empty_deque(deque* deq);
int push_back_deque(deque* deq, double element);
int push_front_deque(deque* deq, double element);
double pop_back_deque(deque* deq);
double pop_front_deque(deque* deq);


    /* LINKED LISTS */

// === smart_elements ===

typedef struct elem elem;

struct elem {
    double value;
    elem* next;
    elem* prev;
};


// === stack by LL ===

typedef struct {
    elem* first;
} dyn_stack;

dyn_stack* create_dyn_stack();
void destroy_dyn_stack(dyn_stack* dst);
int is_empty_dyn_stack(dyn_stack* dst);
int push_back_dyn_stack(dyn_stack* dst, double element);
double pop_back_dyn_stack(dyn_stack* dst);


// === queue by LL ===

typedef struct {
    elem* first;
    elem* last;
} dyn_queue;

dyn_queue* create_dyn_queue();
void destroy_dyn_queue(dyn_queue* dqu);
int is_empty_dyn_queue(dyn_queue* dqu);
int push_back_dyn_queue(dyn_queue* dqu, double element);
double pop_front_dyn_queue(dyn_queue* dqu);


// === deque by LL ===

typedef struct {
    elem* first;
    elem* last;
} dyn_deque;

dyn_deque* create_dyn_deque();
void destroy_dyn_deque(dyn_deque* ddeq);
int is_empty_dyn_deque(dyn_deque* ddeq);
int push_back_dyn_deque(dyn_deque* ddeq, double element);
int push_front_dyn_deque(dyn_deque* ddeq, double element);
double pop_back_dyn_deque(dyn_deque* ddeq);
double pop_front_dyn_deque(dyn_deque* ddeq);
