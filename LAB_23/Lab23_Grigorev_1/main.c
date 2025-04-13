#include "./treeStruct/tree.h"
#include <stdio.h>
#include <float.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printTree(tree t, int depth) {
    if (t == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("%.2f\n", getValue(t));

    printTree(getLeft(t), depth + 1);
    printTree(getRight(t), depth + 1);
}

int main() {
    tree t = createEmpty();
    int choice;
    double val;

    while (1) {
        printf("\nMenu:\n");
        printf("  1. Add node\n");
        printf("  2. Remove node\n");
        printf("  3. Visualize tree\n");
        printf("  4. Check if tree is AVL\n");
        printf("  5. Get tree depth\n");
        printf("  6. Exit\n");
        printf("Choose an action: ");

        // Проверка корректности ввода для выбора действия
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 6) {
            printf("Invalid input. Please enter a number between 1 and 6: ");
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
                printTree(t, 0);

                break;
            }

            case 4: {
                if (checkAVL(t, -DBL_MAX, DBL_MAX) != -1)
                    printf("    The tree is an AVL tree.\n");
                else 
                    printf("    The tree is NOT an AVL tree.\n");
                
                break;
            }

            case 5: {
                int depth = getDepth(t);
                printf("Tree depth: %d\n", depth);

                break;
            }

            case 6: {
                destroyTree(t);
                printf("Tree destroyed. Exiting.\n");

                return 0;
            }
        }
    }
}