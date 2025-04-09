#include "../../../LAB_structs/DIFFICULT_STRUCTS/dbl/queue_dbl.h"
#include "insert_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для печати содержимого дека
void print_deque(deque_dbl* ddbl) {
    printf("Deque: [");
    deque_dbl* temp = ddbl_create(ddbl->max_len);
    
    // Переносим элементы во временный дек и печатаем
    while (!ddbl_is_empty(ddbl)) {
        double val = ddbl_pop_front(ddbl);
        printf("%.2f", val);
        if (!ddbl_is_empty(ddbl)) printf(", ");
        ddbl_push_back(temp, val);
    }
    
    // Возвращаем элементы обратно
    while (!ddbl_is_empty(temp)) {
        ddbl_push_back(ddbl, ddbl_pop_front(temp));
    }
    
    ddbl_destroy(temp);
    printf("]\n");
}

// Testирование сортировки
void test_sort() {
    deque_dbl* ddbl = ddbl_create(10);
    
    // Test 1: Пустой дек
    printf("Test 1: Empty deque\n");
    print_deque(ddbl);
    insert_sort(ddbl);
    print_deque(ddbl);
    printf("\n");
    
    // Test 2: Один элемент
    printf("Test 2: 1 element\n");
    ddbl_push_back(ddbl, 5.0);
    print_deque(ddbl);
    insert_sort(ddbl);
    print_deque(ddbl);
    printf("\n");

    ddbl_destroy(ddbl);
    ddbl = ddbl_create(10);
    
    // Test 3: Уже отсортированный дек
    printf("Test 3: Already sorted deque\n");
    ddbl_push_back(ddbl, 1.0);
    ddbl_push_back(ddbl, 2.0);
    ddbl_push_back(ddbl, 3.0);
    print_deque(ddbl);
    insert_sort(ddbl);
    print_deque(ddbl);
    printf("\n");

    ddbl_destroy(ddbl);
    ddbl = ddbl_create(10);
    
    // Test 4: Обратно отсортированный дек
    printf("Test 4: Reversed sorted deque\n");
    ddbl_push_back(ddbl, 3.0);
    ddbl_push_back(ddbl, 2.0);
    ddbl_push_back(ddbl, 1.0);
    print_deque(ddbl);
    insert_sort(ddbl);
    print_deque(ddbl);
    printf("\n");

    ddbl_destroy(ddbl);
    ddbl = ddbl_create(10);
    
    // Test 5: Случайные элементы
    printf("Test 5: Random elements\n");
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        ddbl_push_back(ddbl, (double)(rand() % 100) / 10.0);
    }
    print_deque(ddbl);
    insert_sort(ddbl);
    print_deque(ddbl);
    printf("\n");
    
    ddbl_destroy(ddbl);
}

int main() {
    test_sort();
    return 0;
}