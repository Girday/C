#include "main.h"

// Счетчики операций
int comparison_count = 0;
int movement_count = 0;

// Функция для настройки кодировки консоли
void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

// Функция для чтения данных из файла
int readData(const char *filename, Table *table) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return 0;
    }
    
    int count = 0;
    char line[MAX_STRING_LENGTH * 2];
    
    while (count < MAX_RECORDS && fgets(line, sizeof(line), file)) {
        char *key = strtok(line, " \n");
        char *value = strtok(NULL, "\n");
        
        if (key && value) {
            // Проверка длины ключа
            if (strlen(key) > KEY_LENGTH) {
                printf("Ошибка: ключ '%s' длиннее %d знаков\n", key, KEY_LENGTH);
                fclose(file);
                return 0;
            }
            
            strncpy(table->keys[count], key, KEY_LENGTH);
            table->keys[count][KEY_LENGTH] = '\0';  // Гарантируем завершающий нуль
            strcpy(table->values[count], value);
            count++;
        }
    }
    
    fclose(file);
    table->count = count;
    return count;
}

// Функция для записи данных в файл
void writeData(const char *filename, Table *table) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла %s для записи\n", filename);
        return;
    }
    
    for (int i = 0; i < table->count; i++) {
        fprintf(file, "%s %s\n", table->keys[i], table->values[i]);
    }
    
    fclose(file);
}

// Функция для выполнения двоичного поиска позиции вставки
int binarySearch(Table *table, int start, int end, const char *key) {
    if (end <= start) {
        comparison_count++;
        return (strcmp(key, table->keys[start]) > 0) ? (start + 1) : start;
    }
    
    int mid = (start + end) / 2;
    
    comparison_count++;
    if (strcmp(key, table->keys[mid]) == 0)
        return mid + 1;
    
    comparison_count++;
    if (strcmp(key, table->keys[mid]) > 0)
        return binarySearch(table, mid + 1, end, key);
    
    return binarySearch(table, start, mid - 1, key);
}

// Метод двоичной вставки
void binaryInsertionSort(Table *table) {
    comparison_count = 0;
    movement_count = 0;
    
    for (int i = 1; i < table->count; i++) {
        char key[KEY_LENGTH + 1];
        char value[MAX_STRING_LENGTH];
        strcpy(key, table->keys[i]);
        strcpy(value, table->values[i]);
        int j = i - 1;
        
        int location = binarySearch(table, 0, j, key);
        
        while (j >= location) {
            strcpy(table->keys[j + 1], table->keys[j]);
            strcpy(table->values[j + 1], table->values[j]);
            movement_count++;
            j--;
        }
        
        strcpy(table->keys[j + 1], key);
        strcpy(table->values[j + 1], value);
        movement_count++;
    }
}

// Функция для поиска записи по ключу (бинарный поиск)
int searchByKey(Table *table, const char *key) {
    int left = 0;
    int right = table->count - 1;
    int search_comparisons = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(key, table->keys[mid]);
        search_comparisons++;
        
        if (cmp == 0)
            return mid;
        
        if (cmp > 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return -1;
}

// Функция для вывода отсортированной таблицы
void printTable(Table *table) {
    printf("Отсортированная таблица:\n");
    
    for (int i = 0; i < table->count; i++) {
        printf("%s %s\n", table->keys[i], table->values[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    setupConsole();
    
    if (argc != 2) {
        printf("Использование: %s <входной_файл>\n", argv[0]);
        return 1;
    }
    
    Table table;
    int count;
    clock_t start, end;
    
    // Чтение данных из входного файла
    count = readData(argv[1], &table);
    if (count == 0) {
        printf("Не удалось прочитать данные из файла %s\n", argv[1]);
        return 1;
    }
    
    // Сортировка данных
    start = clock();
    binaryInsertionSort(&table);
    end = clock();
    
    // Запись отсортированных данных в output.txt
    writeData("output.txt", &table);
    
    // Вывод статистики и отсортированной таблицы
    printTable(&table);
    
    // Демонстрация поиска по ключу
    const char *searchKey = "melon";
    int foundIndex = searchByKey(&table, searchKey);
    
    if (foundIndex != -1)
        printf("Поиск по ключу '%s': найдено на позиции %d, значение: %s\n", 
               searchKey, foundIndex + 1, table.values[foundIndex]);
    else
        printf("Поиск по ключу '%s': не найдено\n", searchKey);
}
