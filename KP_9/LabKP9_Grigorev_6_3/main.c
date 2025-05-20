#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h> // Для функции _access в Windows

#define MAX_STRING_LENGTH 256
#define MAX_RECORDS 1000

// Счетчики операций
int comparison_count = 0;
int movement_count = 0;

// Структура таблицы №3 (пара ключ-значение)
typedef struct {
    char key[MAX_STRING_LENGTH];
    char value[MAX_STRING_LENGTH];
} Record;

// Функция для чтения данных из файла
int readData(const char *filename, Record *table) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return 0;
    }
    
    int count = 0;
    while (count < MAX_RECORDS && fscanf(file, "%s %s", table[count].key, table[count].value) == 2) {
        count++;
    }
    
    fclose(file);
    return count;
}

// Функция для записи данных в файл
void writeData(const char *filename, Record *table, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла %s для записи\n", filename);
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s\n", table[i].key, table[i].value);
    }
    
    fclose(file);
}

// Функция для выполнения двоичного поиска позиции вставки
int binarySearch(Record *table, int start, int end, const char *key) {
    if (end <= start) {
        comparison_count++; // Сравнение для условия в if
        return (strcmp(key, table[start].key) > 0) ? (start + 1) : start;
    }
    
    int mid = (start + end) / 2;
    
    comparison_count++; // Сравнение для условия в if ниже
    if (strcmp(key, table[mid].key) == 0) {
        return mid + 1;
    }
    
    comparison_count++; // Сравнение для условия в if ниже
    if (strcmp(key, table[mid].key) > 0) {
        return binarySearch(table, mid + 1, end, key);
    }
    
    return binarySearch(table, start, mid - 1, key);
}

// Метод двоичной вставки
void binaryInsertionSort(Record *table, int count) {
    // Сброс счетчиков операций
    comparison_count = 0;
    movement_count = 0;
    
    for (int i = 1; i < count; i++) {
        Record key = table[i];
        int j = i - 1;
        
        // Найти позицию для вставки с помощью двоичного поиска
        int location = binarySearch(table, 0, j, key.key);
        
        // Сдвинуть все элементы после location вправо
        while (j >= location) {
            table[j + 1] = table[j];
            movement_count++; // Инкремент при каждом перемещении
            j--;
        }
        
        table[j + 1] = key;
        movement_count++; // Инкремент для финального помещения ключа
    }
}

// Функция для поиска записи по ключу (бинарный поиск)
int searchByKey(Record *table, int count, const char *key) {
    int left = 0;
    int right = count - 1;
    int search_comparisons = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(key, table[mid].key);
        search_comparisons++;
        
        if (cmp == 0) {
            printf("Поиск выполнен за %d сравнений\n", search_comparisons);
            return mid; // Ключ найден
        }
        
        if (cmp > 0) {
            left = mid + 1; // Искать в правой половине
        } else {
            right = mid - 1; // Искать в левой половине
        }
    }
    
    printf("Поиск выполнен за %d сравнений\n", search_comparisons);
    return -1; // Ключ не найден
}

// Функция для вывода статистики сортировки
void printSortStats(clock_t start, clock_t end, int count) {
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время сортировки: %.6f секунд\n", time_spent);
    printf("Количество записей: %d\n", count);
    printf("Количество сравнений: %d\n", comparison_count);
    printf("Количество перемещений: %d\n", movement_count);
    // Среднее число сравнений на одну запись
    printf("Среднее число сравнений на запись: %.2f\n", (float)comparison_count / count);
    // Среднее число перемещений на одну запись
    printf("Среднее число перемещений на запись: %.2f\n", (float)movement_count / count);
}

// Функция для вывода отсортированной таблицы
void printTable(Record *table, int count) {
    printf("Отсортированная таблица (первые 10 записей или меньше):\n");
    int limit = (count < 10) ? count : 10;
    
    for (int i = 0; i < limit; i++) {
        printf("%s %s\n", table[i].key, table[i].value);
    }
    printf("\n");
}

// Функция для создания отчета о эффективности
// void writeReport(const char *filename, const char *dataType, int count, int comparisons, int movements, double time) {
//     FILE *file;
    
//     // Если файл не существует, создаем его и пишем заголовок
//     if (_access(filename, 0) != 0) {
//         file = fopen(filename, "w");
//         fprintf(file, "Отчет о эффективности метода двоичной вставки\n");
//         fprintf(file, "================================================\n\n");
//         fprintf(file, "| Тип данных | Кол-во записей | Сравнения | Перемещения | Время (сек) | Ср. сравнений | Ср. перемещений |\n");
//         fprintf(file, "|------------|----------------|-----------|-------------|-------------|---------------|----------------|\n");
//     } else {
//         file = fopen(filename, "a");
//     }
    
//     if (!file) {
//         printf("Ошибка при открытии файла отчета\n");
//         return;
//     }
    
//     fprintf(file, "| %-10s | %-14d | %-9d | %-11d | %-11.6f | %-13.2f | %-14.2f |\n", 
//            dataType, count, comparisons, movements, time, (float)comparisons / count, (float)movements / count);
    
//     fclose(file);
// }

int main() {
    Record table[MAX_RECORDS];
    int count;
    clock_t start, end;
    double time_spent;
    
    // Создание файла отчета
    // const char *reportFile = "report.txt";
    // remove(reportFile); // Удаляем предыдущий отчет, если существует
    
    // Обработка файла со смешанными данными
    count = readData("tests/mix.txt", table);
    start = clock();
    binaryInsertionSort(table, count);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    writeData("results/mix_s.txt", table, count);
    
    printf("Статистика для mix.txt:\n");
    printSortStats(start, end, count);
    printTable(table, count);
    // writeReport(reportFile, "Смешанные", count, comparison_count, movement_count, time_spent);
    
    // Демонстрация поиска по ключу
    const char *searchKey = "melon";
    int foundIndex = searchByKey(table, count, searchKey);
    if (foundIndex != -1) {
        printf("Поиск по ключу '%s': найдено на позиции %d, значение: %s\n\n", 
               searchKey, foundIndex + 1, table[foundIndex].value);
    } else {
        printf("Поиск по ключу '%s': не найдено\n\n", searchKey);
    }
    
    // Обработка файла с упорядоченными данными
    count = readData("tests/straight.txt", table);
    start = clock();
    binaryInsertionSort(table, count);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    writeData("results/straight_s.txt", table, count);
    
    printf("Статистика для straight.txt:\n");
    printSortStats(start, end, count);
    printTable(table, count);
    // writeReport(reportFile, "Упорядоч.", count, comparison_count, movement_count, time_spent);
    
    // Обработка файла с обратно упорядоченными данными
    count = readData("tests/reverse.txt", table);
    start = clock();
    binaryInsertionSort(table, count);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    writeData("results/reverse_s.txt", table, count);
    
    printf("Статистика для reverse.txt:\n");
    printSortStats(start, end, count);
    printTable(table, count);
    // writeReport(reportFile, "Обратные", count, comparison_count, movement_count, time_spent);
    
    printf("\nОтчет сохранен в файле %s\n", reportFile);
    
    return 0;
}
