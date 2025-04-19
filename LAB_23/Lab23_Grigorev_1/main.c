#include <stdio.h>
#include <float.h>

#include "treeStruct/tree.h"
#include "stackOnTree/stack_tree.h"


                        /* === ОЧИСТКА БУФЕРА ВВОДА === */

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


                        /* === ПЕЧАТЬ ДЕРЕВА === */

void printTree(tree t) {
    stack_tree* stack = stree_create(10);
    stree_push(stack, t);

    while (!stree_is_empty(stack)) {
        tree current = stree_pop(stack);
        
        if (current == NULL) 
            continue;

        int depth = getLevel(t, getValue(current));
        
        for (int i = 0; i < depth; i++)
            printf("    ");
    
        printf("%.2f\n", getValue(current));

        if (!isEmpty(getRight(current)))
            stree_push(stack, getRight(current));
    
        if (!isEmpty(getLeft(current)))
            stree_push(stack, getLeft(current));
    }

    stree_destroy(stack);
}


int main() {
    tree t = createEmpty();
    int choice;
    double val;
    int level;

    while (1) {
        printf("\nMenu:\n");
        printf("  1. Add node\n");
        printf("  2. Remove node\n");
        printf("  3. Visualize tree\n");
        printf("  4. Check if tree is AVL\n");
        printf("  5. Get tree depth\n");
        printf("  6. Get tree width\n");
        printf("  7. Get width at specific level\n");
        printf("  8. Get level of value\n");
        printf("  9. Exit\n");
        printf("Choose an action: ");

        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 9) {
            printf("Invalid input. Please enter a number between 1 and 9: ");
            clearInputBuffer();
        }

        clearInputBuffer();
        printf("\n");

        switch (choice) {
            case 1: {
                printf("Enter value: ");

                while (scanf("%lf", &val) != 1) {
                    printf("Invalid input. Please enter a valid number: ");
                    clearInputBuffer();
                }
                
                clearInputBuffer();

                int result = addNode(&t, val);

                if (result == 1) 
                    printf("Node %.2f added.\n", val);
                else if (result == 0 && t != NULL)
                    printf("Node already exists.\n");
                else
                    printf("Failed to add node (possibly out of memory).\n");
                
                break;
            }

            case 2: {
                printf("Enter value to remove: ");
                
                while (scanf("%lf", &val) != 1) {
                    printf("Invalid input. Please enter a valid number: ");
                    clearInputBuffer();
                }

                clearInputBuffer();

                t = removeNode(t, val);
               
                printf("Node %.2f removed (if it existed).\n", val);
                
                break;
            }

            case 3: {
                printf("Tree:\n");
                printTree(t);
                
                break;
            }

            case 4: {
                if (checkAVL(t))
                    printf("The tree is an AVL tree.\n");
                else 
                    printf("The tree is NOT an AVL tree.\n");
                
                break;
            }

            case 5: {
                int depth = getDepth(t);
                printf("Tree depth: %d\n", depth);
                break;
            }

            case 6: {
                int width = getWidthByBFS(t);
                printf("Tree width: %d\n", width);
                break;
            }

            case 7: {
                printf("Enter level to check width (from level 0): ");
                
                while (scanf("%d", &level) != 1 || level < 0) {
                    printf("Invalid input. Please enter a non-negative integer: ");
                    clearInputBuffer();
                }

                clearInputBuffer();

                int width = levelWidth(t, level);
                printf("Width at level %d: %d\n", level, width);

                break;
            }

            case 8: {
                printf("Enter value to check level: ");
               
                while (scanf("%lf", &val) != 1 || val < 0) {
                    printf("Invalid input. Please enter double: ");
                    clearInputBuffer();
                }

                clearInputBuffer();

                int levelOfVal = getLevel(t, val);
                
                if (levelOfVal == -1)
                    printf("Value %.2f doesn't exist\n", val);
                else
                    printf("Level of value %.2f: %d\n", val, levelOfVal);

                break;
            }

            case 9: {
                destroyTree(t); 
                printf("Tree destroyed. Exiting.\n");

                return 0;
            }
        }
    }
}