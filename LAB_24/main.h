#pragma once

#include "queueOnLexems/queue_lex.h"
#include "stackOnLexems/stack_lex.h"

typedef enum {
    UNEXPECTED_TOKEN,
    SUCCESS
} read_result;

typedef enum {
    MISSING_LP,
    SUCCESS
} i2p_result;

typedef enum {
    UNEXPECTED_TOKEN,
    SUCCESS
} p2t_result;

read_result readline(queue_lex* out);
i2p_result infix2postfix(queue_lex* q, queue_lex* out);