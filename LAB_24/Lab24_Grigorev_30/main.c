#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "token/token.h"


static ErrorCode getErrCode(ErrorInfo* error) {
    return error -> code;
}

static int getErrPos(ErrorInfo* error) {
    return error -> position;
}

static const char* getErrMes(ErrorInfo* error) {
    return error -> message;
}


static int is_op_char(char c) {
    return strchr("+-*/^!~", c) != NULL && c != 'e' && c != 'E';
}

static int is_right_assoc(Token token) {
    return token.value[0] == '^' || token.value[0] == '~';
}

static int op_priority(Token token) {
    switch (token.value[0]) {
        case '!': 
        case '~': 
            return 4;
        case '^':           
            return 3;
        case '*': 
        case '/': 
            return 2;
        case '+': 
        case '-': 
            return 1;
        default:           
            return 0;
    }
}

static int should_displace(Token lex, Token target) {
    if (target.type == TOK_PAREN && target.value[0] == '(') 
        return 0;
    
    int lex_prio = op_priority(lex);
    int target_prio = op_priority(target);
    
    return is_right_assoc(lex) || lex.value[0] == '!' ? target_prio > lex_prio : target_prio >= lex_prio;
}

read_result readline(queue_lex* out) {
    read_result result = {out, {RESULT_OK, "Success", -1}};
    char buffer[256];
    int buffer_pos = 0;
    int pos = 0;
    int prev_type = -1;
    char last_paren_type = '\0';
    int c = getchar();

    if (out == NULL) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Output queue is NULL", -1};
        return result;
    }

    while (c != EOF && c != '\n') {
        if (isspace(c)) {
            c = getchar();
            pos++;

            continue;
        }

        buffer_pos = 0;

        if (prev_type == -1 && is_op_char(c) && c != '-') {
            buffer[0] = c;
            buffer[1] = '\0';
            result.error = (ErrorInfo){ERROR_INVALID_EXPRESSION, 
                                      "Expression cannot start with this operator", pos};

            free(strdup(buffer));

            return result;
        }

        if (isdigit(c) || (c == '.' && (c = getchar(), isdigit(c)))) {
            ungetc(c, stdin);
            
            if (c == '.') 
                c = '.'; 
            else 
                c = getchar();
            
            int is_hex = 0, is_bin = 0, has_exponent = 0, has_decimal = 0;
            
            if (c == '0') {
                buffer[buffer_pos++] = c;
                c = getchar();
            
                if (tolower(c) == 'x') { 
                    is_hex = 1; 
                    buffer[buffer_pos++] = c; 
                    c = getchar(); 
                }
                else if (tolower(c) == 'b') { 
                    is_bin = 1; 
                    buffer[buffer_pos++] = c; 
                    c = getchar(); 
                }
            }

            while (1) {
                if (is_hex) {
                    if (isxdigit(c)) { 
                        buffer[buffer_pos++] = c; 
                        c = getchar(); 
                    }
                    else if (tolower(c) == 'p' && !has_exponent) {
                        has_exponent = 1;
                        buffer[buffer_pos++] = c;
                        c = getchar();
                        
                        if (c == '+' || c == '-') { 
                            buffer[buffer_pos++] = c; 
                            c = getchar(); 
                        }
                    } 
                    else 
                        break;
                } 
                else if (is_bin) {
                    if (c == '0' || c == '1') { 
                        buffer[buffer_pos++] = c;
                        c = getchar(); 
                    }
                    else 
                        break;
                } 
                else {
                    if (isdigit(c)) { 
                        buffer[buffer_pos++] = c; 
                        c = getchar(); 
                    }
                    else if (c == '.' && !has_decimal && !has_exponent) {
                        has_decimal = 1;
                        buffer[buffer_pos++] = c;
                        c = getchar();
                    } 
                    else if (tolower(c) == 'e' && !has_exponent) {
                        has_exponent = 1;
                        buffer[buffer_pos++] = c;
                        c = getchar();
                        
                        if (c == '+' || c == '-') { 
                            buffer[buffer_pos++] = c; 
                            c = getchar(); 
                        }
                    } 
                    else 
                        break;
                }
                
                if (buffer_pos >= 255) {
                    result.error = (ErrorInfo){ERROR_INVALID_SYMBOL, "Numeric constant too long", pos};
                    return result;
                }
            }

            buffer[buffer_pos] = '\0';
            
            if (buffer[buffer_pos-1] == 'e' || buffer[buffer_pos-1] == 'p' || 
                buffer[buffer_pos-1] == '+' || buffer[buffer_pos-1] == '-') {
                result.error = (ErrorInfo){ERROR_INVALID_SYMBOL, "Invalid numeric constant", pos};
                
                return result;
            }

            Token token = {strdup(buffer), TOK_CONST};
            
            if (!qlex_push_back(out, token)) {
                free(token.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
            
                return result;
            }
            
            prev_type = TOK_CONST;
            pos += buffer_pos;
            
            continue;
        }

        if (isalpha(c) || c == '_') {
            while (isalnum(c) || c == '_') {
                buffer[buffer_pos++] = c;
                c = getchar();
            }
            
            buffer[buffer_pos] = '\0';
            
            Token token = {strdup(buffer), TOK_VAR};
            
            if (!qlex_push_back(out, token)) {
                free(token.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
            
                return result;
            }
            
            prev_type = TOK_VAR;
            pos += buffer_pos;
            
            continue;
        }

        if (is_op_char(c) || c == '(' || c == ')') {
            buffer[0] = c;
            buffer[1] = '\0';
            Token token;
            
            if (c == '-') {
                int next_c = getchar();
                ungetc(next_c, stdin);

                if (prev_type == -1 || prev_type == TOK_OP || prev_type == TOK_UNARY_OP ||
                   (prev_type == TOK_PAREN && last_paren_type == '('))
                    token = (Token){strdup("~"), TOK_UNARY_OP};
                else
                    token = (Token){strdup(buffer), TOK_OP};
            }
            else if (c == '(' || c == ')') {
                token = (Token){strdup(buffer), TOK_PAREN};
                last_paren_type = c;
            }
            else if (c == '!') 
                token = (Token){strdup(buffer), TOK_UNARY_OP};
            
            else 
                token = (Token){strdup(buffer), TOK_OP};
            
            
            if (!qlex_push_back(out, token)) {
                free(token.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                
                return result;
            }

            prev_type = token.type;
            c = getchar();
            pos++;
            
            continue;
        }

        result.error = (ErrorInfo){ERROR_INVALID_SYMBOL, "Invalid character in input", pos};
        
        return result;
    }

    if (pos > 0 && prev_type == TOK_OP) {
        Token last_token = qlex_top(out);

        if (!(last_token.type == TOK_UNARY_OP && strcmp(last_token.value, "!") == 0)) {
            result.error = (ErrorInfo){ERROR_INVALID_EXPRESSION, 
                                      "Expression can only end with factorial operator '!'", pos-1};
            return result;
        }
    }

    if (pos == 0)
        result.error = (ErrorInfo){ERROR_EMPTY_INPUT, "Empty input line", -1};

    return result;
}

postfix_result convertToPostfix(queue_lex* q, queue_lex* out) {
    postfix_result result = {out, {RESULT_OK, "Success", -1}};
    
    if (q == NULL || out == NULL) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Input or output queue is NULL", -1};
        return result;
    }

    stack_lex* s = slex_create(10);
    
    if (s == NULL) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create stack", -1};
        return result;
    }

    int pos = 0;
    while (!qlex_is_empty(q)) {
        Token lex = qlex_pop_front(q);
        
        if (lex.type == TOK_CONST || lex.type == TOK_VAR) {
            if (!qlex_push_back(out, lex)) {
                free(lex.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                slex_destroy(s);
          
                return result;
            }
        } 
        else if (lex.type == TOK_PAREN && strcmp(lex.value, "(") == 0) {
            if (!slex_push_back(s, lex)) {
                free(lex.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
                slex_destroy(s);
          
                return result;
            }
        } 
        else if (lex.type == TOK_PAREN && strcmp(lex.value, ")") == 0) {
            while (!slex_is_empty(s) && strcmp(slex_top(s).value, "(") != 0) {
                if (!qlex_push_back(out, slex_pop_back(s))) {
                    result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                    slex_destroy(s);
          
                    return result;
                }
            }

            if (slex_is_empty(s)) {
                free(lex.value);
                result.error = (ErrorInfo){ERROR_UNBALANCED_PARENS, "Unbalanced parentheses", pos};
                slex_destroy(s);
            
                return result;
            }

            Token open_paren = slex_pop_back(s);

            free(open_paren.value);
            free(lex.value);
        } 
        else if (lex.type == TOK_OP || lex.type == TOK_UNARY_OP) {
            while (!slex_is_empty(s) && strcmp(slex_top(s).value, "(") != 0 && should_displace(lex, slex_top(s))) {
                if (!qlex_push_back(out, slex_pop_back(s))) {
                    free(lex.value);
                    result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                    slex_destroy(s);
                    
                    return result;
                }
            }

            if (!slex_push_back(s, lex)) {
                free(lex.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
                slex_destroy(s);
            
                return result;
            }
        } 
        else {
            free(lex.value);
            result.error = (ErrorInfo){ERROR_INVALID_SYMBOL, "Invalid token type", pos};
            slex_destroy(s);
            
            return result;
        }

        pos++;
    }

    while (!slex_is_empty(s)) {
        Token op = slex_pop_back(s);
        
        if (strcmp(op.value, "(") == 0) {
            free(op.value);
            result.error = (ErrorInfo){ERROR_UNBALANCED_PARENS, "Unbalanced parentheses", pos};
            slex_destroy(s);
        
            return result;
        }

        if (!qlex_push_back(out, op)) {
            free(op.value);
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
            slex_destroy(s);
        
            return result;
        }
    }

    slex_destroy(s);
    
    return result;
}

tree_result convertToTree(queue_lex* q) {
    tree_result result = {NULL, {RESULT_OK, "Success", -1}};
    
    if (qlex_is_empty(q)) {
        result.error = (ErrorInfo){ERROR_EMPTY_INPUT, "Empty input queue", -1};
        return result;
    }

    stack_tree* stack = stree_create(10);

    if (!stack) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create stack", -1};
        return result;
    }

    int pos = 0;
    
    while (!qlex_is_empty(q)) {
        Token token = qlex_pop_front(q);
        tree node = build(token, NULL, NULL);
        
        if (!node) {
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create tree node", pos};
            stree_destroy(stack);
    
            return result;
        }

        if (token.type == TOK_OP || token.type == TOK_UNARY_OP) {
            if (token.value[0] == '~') {
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){ERROR_STACK_UNDERFLOW, "Missing operand for ~", pos};
                    destroyTree(node);
                    stree_destroy(stack);
    
                    return result;
                }
    
                node = build(getValue(node), getLeft(node), stree_pop_back(stack));
            } 
            else if (token.value[0] == '!') {
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){ERROR_STACK_UNDERFLOW, "Missing operand for !", pos};
                    destroyTree(node);
                    stree_destroy(stack);
    
                    return result;
                }
    
                node = build(getValue(node), stree_pop_back(stack), getRight(node));
            } 
            else {
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){ERROR_STACK_UNDERFLOW, "Missing right operand", pos};
                    destroyTree(node);
                    stree_destroy(stack);
    
                    return result;
                }
    
                node = build(getValue(node), getLeft(node), stree_pop_back(stack));
                
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){ERROR_STACK_UNDERFLOW, "Missing left operand", pos};
                    destroyTree(getRight(node));
                    destroyTree(node);
                    stree_destroy(stack);
    
                    return result;
                }
    
                node = build(getValue(node), stree_pop_back(stack), getRight(node));
            }
        }

        if (!stree_push_back(stack, node)) {
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
            destroyTree(node);
            stree_destroy(stack);
    
            return result;
        }
    
        pos++;
    }

    result.root = stree_pop_back(stack);
    
    if (!stree_is_empty(stack)) {
        result.error = (ErrorInfo){ERROR_STACK_REMAINING, "Extra nodes in stack after processing", pos};
        destroyTree(result.root);
        result.root = NULL;
    }

    stree_destroy(stack);
    
    return result;
}

int needsParentheses(Token parent, Token child, int isLeftChild) {
    if (child.type != TOK_OP && child.type != TOK_UNARY_OP) 
        return 0;
   
    if (parent.type != TOK_OP && parent.type != TOK_UNARY_OP) 
        return 0;
    
    int parentPrio = op_priority(parent);
    int childPrio = op_priority(child);
    
    if (childPrio < parentPrio) 
        return 1;
    
    if (childPrio == parentPrio) {
        if (!is_right_assoc(parent) && !isLeftChild) 
            return 0;
        
        return 1;
    }

    return 0;
}

void buildInfixString(tree t, Token parent, int isLeftChild, char** buffer, int* size) {
    if (isEmpty(t)) 
        return;

    Token current = getValue(t);
    int needParen = needsParentheses(parent, current, isLeftChild);

    if (needParen) {
        strcat(*buffer, "(");
        (*size)++;
    }

    if (current.type == TOK_UNARY_OP && strcmp(current.value, "~") == 0) {
        strcat(*buffer, "-");
        (*size)++;
    }

    if (current.type == TOK_OP || current.type == TOK_UNARY_OP) {
        if (getLeft(t) != NULL) 
            buildInfixString(getLeft(t), current, 1, buffer, size);

        if (!(current.type == TOK_UNARY_OP && strcmp(current.value, "~") == 0)) {
            strcat(*buffer, current.value);
            (*size) += strlen(current.value);
        }

        buildInfixString(getRight(t), current, 0, buffer, size);
    } 
    else {
        strcat(*buffer, current.value);
        (*size) += strlen(current.value);
    }

    if (needParen) {
        strcat(*buffer, ")");
        (*size)++;
    }
}

char* treeToInfix(tree t) {
    if (isEmpty(t)) 
        return strdup("");

    int estimatedSize = 256;
    char* buffer = malloc(estimatedSize);
    
    if (!buffer) 
        return NULL;
    
    buffer[0] = '\0';

    int actualSize = 0;
    Token dummy = {"", TOK_CONST};

    buildInfixString(t, dummy, 1, &buffer, &actualSize);
    free(buffer);

    buffer = malloc(actualSize + 1);
    
    if (!buffer) 
        return NULL;
    
    buffer[0] = '\0';

    int tmpSize = 0;
    buildInfixString(t, dummy, 1, &buffer, &tmpSize);

    return buffer;
}

void print_error(ErrorInfo* error) {
    const char* error_type = "";
    
    switch (getErrCode(error)) {
        case ERROR_EMPTY_INPUT:       
            error_type = "Empty input"; 
            break;
        case ERROR_INVALID_SYMBOL:    
            error_type = "Invalid symbol"; 
            break;
        case ERROR_UNBALANCED_PARENS: 
            error_type = "Unbalanced parentheses"; 
            break;
        case ERROR_STACK_UNDERFLOW:   
            error_type = "Stack underflow"; 
            break;
        case ERROR_STACK_REMAINING:   
            error_type = "Remaining elements in stack"; 
            break;
        case ERROR_MEMORY_ALLOC:      
            error_type = "Memory allocation failed"; 
            break;
        case ERROR_INVALID_EXPRESSION:
            error_type = "Invalid expression"; 
            break;
        default:                      
            error_type = "Unknown error"; 
            break;
    }
    
    if (getErrPos(error) >= 0) 
        fprintf(stderr, "Error [%s] at position %d: %s\n", 
                error_type, getErrPos(error), getErrMes(error));
    else 
        fprintf(stderr, "Error [%s]: %s\n", error_type, getErrMes(error));
}

int main() {
    queue_lex* input_queue = qlex_create(1);
   
    if (input_queue == NULL) {
        fprintf(stderr, "Error: Failed to create input queue\n");
        return EXIT_FAILURE;
    }

    printf("\nEnter expression: ");
    read_result read_res = readline(input_queue);
   
    if (read_res.error.code != RESULT_OK) {
        print_error(&read_res.error);
        qlex_destroy(input_queue);
   
        return EXIT_FAILURE;
    }

    printf("\nInput expression: ");
    print_queue(input_queue);
    printf("\n");

    queue_lex* postfix_queue = qlex_create(1);
   
    if (postfix_queue == NULL) {
        fprintf(stderr, "Error: Failed to create postfix queue\n");
        qlex_destroy(input_queue);
   
        return EXIT_FAILURE;
    }

    postfix_result postfix_res = convertToPostfix(input_queue, postfix_queue);
    
    if (postfix_res.error.code != RESULT_OK) {
        print_error(&postfix_res.error);
        qlex_destroy(input_queue);
        qlex_destroy(postfix_queue);
    
        return EXIT_FAILURE;
    }

    printf("Postfix notation: ");
    print_queue(postfix_queue);
    printf("\n");

    tree_result tree_res = convertToTree(postfix_queue);
    
    if (tree_res.error.code != RESULT_OK) {
        print_error(&tree_res.error);
        qlex_destroy(input_queue);
        qlex_destroy(postfix_queue);
    
        return EXIT_FAILURE;
    }

    printf("\nExpression tree:\n");
    printTreePretty(tree_res.root, 0);

    deleteUnitMultiply(&tree_res.root);
    applyReorder(&tree_res.root);
    printf("\nReordered tree:\n");
    printTreePretty(tree_res.root, 0);

    char* infix = treeToInfix(tree_res.root);
    
    if (infix) {
        printf("\nInfix expression: %s\n", infix);
        free(infix);
    }

    qlex_destroy(input_queue);
    qlex_destroy(postfix_queue);
    destroyTree(tree_res.root);

    return EXIT_SUCCESS;
}
