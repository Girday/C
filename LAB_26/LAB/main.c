#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insert_sorting_str.h"

char* read_line() {
    int capacity = 128;
    int len = 0;

    char* buffer = malloc(capacity);

    if (!buffer) 
        return NULL;
    
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        buffer[len++] = (char)c;

        if (len >= capacity - 1) {
            capacity *= 2;
            char* tmp = realloc(buffer, capacity);

            if (!tmp) {
                free(buffer);
                return NULL;
            }

            buffer = tmp;
        }
    }

    buffer[len] = '\0';

    if (c == EOF && len == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

int main() {
    deque_str* deque = dstr_create(10);

    if (!deque) {
        fprintf(stderr, "Creating deque of strings failed\n");
        return 1;
    }
    
    printf("Enter lines (empty line to finish):\n");

    while (1) {
        char* line = read_line();
        
        if (!line)
            break;

        if (line[0] == '\0') {
            free(line);
            break;
        }

        if (!dstr_push_back(deque, line)) {
            fprintf(stderr, "Can't add the line\n");
            free(line);
            dstr_destroy(deque);
            return 1;
        }

        free(line);
    }
    
    insert_sort(deque);
    
    printf("\nSorted lines:\n");

    while (!dstr_is_empty(deque)) {
        char* s = dstr_pop_front(deque);
        printf("%s\n", s);
        free(s);
    }
    
    dstr_destroy(deque);
    return 0;
}