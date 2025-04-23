#include "main.h"
#include <stdlib.h>
#include <stdio.h>

static int is_var(char c) {

}

static int is_const(char c) {

}

static int is_op(char c) {

}

static int is_p_left(char c) {
    return c == '(';
}

static int is_p_right(char c) {
    return c == ')';
}

static int is_right_ass(char lex) {

}

static int is_left_ass(char lex) {
    
}

static int should_displace(char lex, char target) {
    if (is_p_left(target))
        return 0;
    
    if (is_right_ass(lex))
} 

read_result readline(queue_lex* out) {
    int prev = 0, cur = getchar();

    while (cur != EOF && cur != '\n') {
        if (is_const(cur) || is_var(cur)) 
            qchr_push(out, cur);

        else if (is_op(cur)) {
            if (cur == '-') {
                if (prev == 0 || is_op(prev) || is_p_left(prev))
                    qchr_push(out, '~');
                else 
                    qchr_push(out, cur);
            }
            else 
                qchr_push(out, cur);
        }
        else 
            return UNEXPECTED_TOKEN;
        
        prev = cur;
    }

    return SUCCESS;
}

i2p_result infix2postfix(queue_lex* q, queue_lex* out) {
    stack_lex* s = slex_create(10);
    char lex;

    while (!qchr_is_empty(q)) {
        lex = qchr_pop(q);

        if (is_const(lex) || is_var(lex)) 
            qchr_push(out, lex);
        else if (is_p_left(lex))
            slex_push(s, lex);
        else if (is_p_right(lex)) {
            while (!slex_is_empty(s) && (lex = slex_pop(s)) != '(')
                qchr_push(out, lex);
        
            if (!is_p_left(lex))
                return MISSING_LP;
        }
        else if (is_op(lex)) {
            while (!slex_is_empty(s) && should_displace(lex, slex_top(s)))
                qchr_push(out, slex_pop(s));

            slex_push(s, lex);
        }
    }

    while (!slex_is_empty(s) && (lex = slex_pop(s)) != '(')
        qchr_push(out, lex);

    if (is_p_left(lex))
        return MISSING_LP;
    
    slex_destroy(s);

    return SUCCESS;
}

