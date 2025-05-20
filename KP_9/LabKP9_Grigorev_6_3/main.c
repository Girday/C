#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 20  // Минимум 13 элементов для структуры №3
#define KEY_LEN 5       // Длина ключа (строковый, 5 байт)

typedef struct {
    char key[KEY_LEN + 1];  // Ключ (строка длиной 5)
    char text[100];         // Текст записи (фрагмент стихотворения/прозы)
} Record;

// Функция для вывода таблицы
void printTable(Record table[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s: %s\n", table[i].key, table[i].text);
    }
    printf("\n");
}

// Бинарный поиск позиции для вставки
int binarySearch(Record table[], int left, int right, char key[]) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(table[mid].key, key);
        if (cmp <= 0) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

// Сортировка двоичными вставками
void binaryInsertionSort(Record table[], int n) {
    for (int i = 1; i < n; i++) {
        Record current = table[i];
        int j = i - 1;
        int pos = binarySearch(table, 0, i - 1, current.key);

        // Сдвиг элементов
        while (j >= pos) {
            table[j + 1] = table[j];
            j--;
        }
        table[pos] = current;
    }
}

// Двоичный поиск по ключу в отсортированной таблице
int binarySearchByKey(Record table[], int n, char key[]) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(table[mid].key, key);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;  // Ключ не найден
}

int main() {
    Record table[MAX_RECORDS];
    int n = 0;

    // Чтение данных из stdin (можно использовать файлы через переадресацию)
    while (scanf("%s", table[n].key) != EOF) {
        // Чтение текста записи (до '\n')
        int c;
        while ((c = getchar()) != '\n' && c != EOF);  // Очистка буфера
        fgets(table[n].text, sizeof(table[n].text), stdin);
        // Удаление символа новой строки
        table[n].text[strcspn(table[n].text, "\n")] = '\0';
        n++;
    }

    printf("Исходная таблица:\n");
    printTable(table, n);

    // Сортировка
    binaryInsertionSort(table, n);
    printf("Отсортированная таблица:\n");
    printTable(table, n);

    // Поиск ключей
    char key[KEY_LEN + 1];
    printf("Введите ключ для поиска (или 'exit' для завершения):\n");
    while (scanf("%s", key) && strcmp(key, "exit") != 0) {
        int index = binarySearchByKey(table, n, key);
        if (index != -1) {
            printf("Найдено: %s: %s\n", table[index].key, table[index].text);
        } else {
            printf("Ключ '%s' не найден.\n", key);
        }
    }

    return 0;
}