#pragma once

typedef enum {
    TOK_VAR,
    TOK_CONST,
    TOK_OP,
    TOK_UNARY_OP,
    TOK_PAREN
} TokenType;

typedef struct {
    char* value;
    TokenType type;
} Token;
