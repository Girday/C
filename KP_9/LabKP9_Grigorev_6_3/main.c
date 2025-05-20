#include "main.h"

int comparison_count = 0;
int movement_count = 0;

void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void printHelp() {
    printf("Использование: program [опции] <входной_файл>\n\n");
    printf("Опции:\n");
    printf("  %s <ключ>    Поиск записи по ключу\n", KEY_SEARCH);
    printf("  %s [N]       Вывод последних N строк (по умолчанию %d)\n", KEY_TAIL, DEFAULT_TAIL_LINES);
    printf("  %s           Вывод статистики сортировки\n", KEY_STATS);
    printf("  %s           Тихий режим (без вывода таблицы)\n", KEY_QUIET);
    printf("  %s           Показать эту справку\n", KEY_HELP);
    printf("\nПримеры:\n");
    printf("  program -s apple input.txt    Поиск записи с ключом 'apple'\n");
    printf("  program -t 5 input.txt        Вывод последних 5 строк\n");
    printf("  program -i input.txt          Вывод статистики сортировки\n");
}

void printStats() {
    printf("\nСтатистика сортировки:\n");
    printf("Количество сравнений: %d\n", comparison_count);
    printf("Количество перемещений: %d\n", movement_count);
}

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
            if (strlen(key) > KEY_LENGTH) {
                printf("Ошибка: ключ '%s' длиннее %d знаков\n", key, KEY_LENGTH);
                fclose(file);

                return 0;
            }
            
            strncpy(table -> keys[count], key, KEY_LENGTH);
            table -> keys[count][KEY_LENGTH] = '\0';
            strcpy(table -> values[count], value);

            count++;
        }
    }
    
    fclose(file);
    table -> count = count;
    
    return count;
}

void writeData(const char *filename, Table *table) {
    FILE *file = fopen(filename, "w");

    if (!file) {
        printf("Ошибка открытия файла %s для записи\n", filename);
        return;
    }
    
    for (int i = 0; i < table -> count; i++)
        fprintf(file, "%s %s\n", table -> keys[i], table -> values[i]);
    
    fclose(file);
}

int binarySearch(Table *table, int start, int end, const char *key) {
    if (end <= start) {
        comparison_count++;
        return (strcmp(key, table -> keys[start]) > 0) ? (start + 1) : start;
    }
    
    int mid = (start + end) / 2;
    
    comparison_count++;
    if (strcmp(key, table -> keys[mid]) == 0)
        return mid + 1;
    
    comparison_count++;
    if (strcmp(key, table -> keys[mid]) > 0)
        return binarySearch(table, mid + 1, end, key);
    
    return binarySearch(table, start, mid - 1, key);
}

void binaryInsertionSort(Table *table) {
    comparison_count = 0;
    movement_count = 0;
    
    for (int i = 1; i < table -> count; i++) {
        char key[KEY_LENGTH + 1];
        char value[MAX_STRING_LENGTH];
        strcpy(key, table -> keys[i]);
        strcpy(value, table -> values[i]);
        int j = i - 1;
        
        int location = binarySearch(table, 0, j, key);
        
        while (j >= location) {
            strcpy(table -> keys[j + 1], table -> keys[j]);
            strcpy(table -> values[j + 1], table -> values[j]);
            movement_count++;
            j--;
        }
        
        strcpy(table -> keys[j + 1], key);
        strcpy(table -> values[j + 1], value);

        movement_count++;
    }
}

int searchByKey(Table *table, const char *key) {
    int left = 0;
    int right = table -> count - 1;
    int search_comparisons = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(key, table -> keys[mid]);
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

void printTable(Table *table, int lines) {
    printf("\nОтсортированная таблица:\n\n");
    
    int start = (lines > 0 && lines < table -> count) ? table -> count - lines : 0;
    
    for (int i = start; i < table -> count; i++)
        printf("%s %s\n", table -> keys[i], table -> values[i]);
    
    printf("\n");
}

int main(int argc, char *argv[]) {
    setupConsole();
    
    if (argc < 2) {
        printHelp();
        return 1;
    }
    
    if (strcmp(argv[1], KEY_HELP) == 0) {
        printHelp();
        return 0;
    }
    
    char *input_file = NULL;
    char *search_key = NULL;
    int tail_lines = 0;
    int show_stats = 0;
    int quiet_mode = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], KEY_SEARCH) == 0 && i + 1 < argc)
            search_key = argv[++i];

        else if (strcmp(argv[i], KEY_TAIL) == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-')
                tail_lines = atoi(argv[++i]);
            else
                tail_lines = DEFAULT_TAIL_LINES;
        }
        else if (strcmp(argv[i], KEY_STATS) == 0)
            show_stats = 1;

        else if (strcmp(argv[i], KEY_QUIET) == 0)
            quiet_mode = 1;
        
        else if (argv[i][0] != '-')
            input_file = argv[i];
    }
    
    if (!input_file) {
        printf("Ошибка: не указан входной файл\n");
        printHelp();

        return 1;
    }
    
    Table table;
    int count;
    
    count = readData(input_file, &table);
    if (count == 0) {
        printf("Не удалось прочитать данные из файла %s\n", input_file);
        return 1;
    }
            
    binaryInsertionSort(&table);
    
    writeData("output.txt", &table);
    
    if (show_stats)
        printStats();
    
    if (!quiet_mode)
        printTable(&table, tail_lines);
    
    if (search_key) {
        int foundIndex = searchByKey(&table, search_key);

        if (foundIndex != -1)
            printf("Поиск по ключу '%s': найдено на позиции %d, значение: %s\n", 
                   search_key, foundIndex + 1, table.values[foundIndex]);
        else
            printf("Поиск по ключу '%s': не найдено\n", search_key);
    }
}
