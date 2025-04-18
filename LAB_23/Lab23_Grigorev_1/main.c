#include "treeStruct/tree.h"
#include "stackOnTree/stack_tree.h"
#include <stdio.h>
#include <float.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


                        /* === ПЕЧАТЬ ДЕРЕВА === */

/* === Итеративная реализация === */

// void printTree(tree t) {
//     stack_tree* stack = stree_create(10);  // Создаем стек
//     stree_push(stack, t);  // Добавляем корень в стек

//     while (!stree_is_empty(stack)) {
//         tree current = stree_pop(stack);  // Извлекаем узел
//         if (current == NULL) 
//             continue;

//         // Печать текущего узла
//         int depth = stree_get_size(stack);  // Глубина соответствует текущему размеру стека
//         for (int i = 0; i < depth; i++) {
//             printf("    ");
//         }
//         printf("%.2f\n", getValue(current));

//         // Сначала правый, затем левый ребёнок
//         if (!isEmpty(getRight(current))) {
//             stree_push(stack, getRight(current));
//         }
//         if (!isEmpty(getLeft(current))) {
//             stree_push(stack, getLeft(current));
//         }
//     }

//     stree_destroy(stack);  // Освобождаем память
// }

/* === Рекурсивная реализация === */

void printTree(tree t, int depth) {
    if (t == NULL)
        return;

    // Отступы для визуализации уровня
    for (int i = 0; i < depth; i++)
        printf("    ");

    // Печать значения текущего узла
    printf("%.2f\n", getValue(t));

    // Печать правого ребёнка
    if (!isEmpty(getRight(t))) {
        for (int i = 0; i < depth + 1; i++)
            printf("    ");

        printf("R\n");
        printTree(getRight(t), depth + 1);
    }
    
    // Печать левого ребёнка
    if (!isEmpty(getLeft(t))) {
        for (int i = 0; i < depth + 1; i++)
            printf("    ");

        printf("L\n");
        printTree(getLeft(t), depth + 1);
    }
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
        printf("  8. Exit\n");
        printf("Choose an action: ");

        // Проверка корректности ввода для выбора действия
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 8) {
            printf("Invalid input. Please enter a number between 1 and 8: ");
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
                destroyTree(t);
                printf("Tree destroyed. Exiting.\n");

                return 0;
            }
        }
    }
}