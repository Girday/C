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
        printf("  5. Exit\n");
        printf("Choose an action: ");


        /*  ДОБАВИТЬ ОБРАБОТКУ EOF, ЧТОБЫ ДЕЛАТЬ DESTROY(T), ИНАЧЕ БУДЕТ УТЕЧКА ПАМЯТИ */


        // Проверка корректности ввода для выбора действия
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("Invalid input. Please enter a number between 1 and 5: ");
            clearInputBuffer(); // Очищаем буфер ввода
        }
        clearInputBuffer(); // Очищаем буфер после успешного ввода
        printf("\n");

        switch (choice) {
            case 1: {
                printf("Enter value: ");
                // Проверка корректности ввода для значения узла
                while (scanf("%lf", &val) != 1) {
                    printf("Invalid input. Please enter a valid number: ");
                    clearInputBuffer();
                }
                clearInputBuffer();

                int result = add(&t, val);

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
                // Проверка корректности ввода для значения узла
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
                destroyRecursive(t);
                printf("Tree destroyed. Exiting.\n");
                return 0;
            }
        }
    }
}