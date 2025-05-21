#include "main.h"
#include <sys/stat.h>

int comparison_count = 0;
int movement_count = 0;

void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void printHelp() {
    printf("Использование: program [опции] <входной_файл>\n\n");
    printf("Опции:\n");
    printf("  %s [N]       Вывод последних N строк (по умолчанию %d)\n", KEY_TAIL, DEFAULT_TAIL_LINES);
    printf("  %s           Вывод статистики сортировки\n", KEY_STATS);
    printf("  %s           Тихий режим (без вывода таблицы)\n", KEY_QUIET);
    printf("  %s           Показать эту справку\n", KEY_HELP);
    printf("\nПримеры:\n");
    printf("  program -t 5 tests/big.txt        Вывод последних 5 строк\n");
    printf("  program -i tests/big.txt          Вывод статистики сортировки\n");
}

void printStats() {
    printf("\nСтатистика сортировки:\n");
    printf("\n  Количество сравнений: %d\n", comparison_count);
    printf("  Количество перемещений: %d\n", movement_count);
}

int readData(const char *filename, Table *table) {
    char key_filename[256];
    char value_filename[256];
    
    snprintf(key_filename, sizeof(key_filename), "tests/keys/%s", filename);
    snprintf(value_filename, sizeof(value_filename), "tests/values/%s", filename);

    FILE *key_file = fopen(key_filename, "r");
    if (!key_file) {
        printf("Ошибка открытия файла ключей %s\n", key_filename);
        return 0;
    }
    
    FILE *value_file = fopen(value_filename, "r");
    if (!value_file) {
        printf("Ошибка открытия файла значений %s\n", value_filename);
        fclose(key_file);
        return 0;
    }
    
    int count = 0;
    char key_line[MAX_STRING_LENGTH];
    char value_line[MAX_STRING_LENGTH];
    
    while (count < MAX_RECORDS &&
           fgets(key_line, sizeof(key_line), key_file) &&
           fgets(value_line, sizeof(value_line), value_file)) {

        key_line[strcspn(key_line, "\n")] = '\0';
        value_line[strcspn(value_line, "\n")] = '\0';
        
        if (strlen(key_line) > KEY_LENGTH) {
            printf("Ошибка: ключ '%s' длиннее %d знаков\n", key_line, KEY_LENGTH);
            
            fclose(key_file);
            fclose(value_file);

            return 0;
        }
        
        if (strlen(key_line) == 0 || strlen(value_line) == 0) {
            printf("Ошибка: пустой ключ или значение в строке %d\n", count + 1);
            
            fclose(key_file);
            fclose(value_file);

            return 0;
        }
        
        strncpy(table -> keys[count], key_line, KEY_LENGTH);
        table -> keys[count][KEY_LENGTH] = '\0';
        
        strncpy(table -> values[count], value_line, MAX_STRING_LENGTH - 1);
        table -> values[count][MAX_STRING_LENGTH - 1] = '\0';
        
        count++;
    }
    
    if (fgets(key_line, sizeof(key_line), key_file) || fgets(value_line, sizeof(value_line), value_file)) {
        printf("Ошибка: разное количество строк в файлах ключей и значений\n");

        fclose(key_file);
        fclose(value_file);

        return 0;
    }
    
    fclose(key_file);
    fclose(value_file);

    table -> count = count;
    
    return count;
}

void writeData(const char *filename, Table *table) {
    mkdir("output");

    char key_filename[256];
    char value_filename[256];
    
    snprintf(key_filename, sizeof(key_filename), "output/keys_out.txt");
    snprintf(value_filename, sizeof(value_filename), "output/values_out.txt");
    
    FILE *key_file = fopen(key_filename, "w");
    if (!key_file) {
        printf("Ошибка открытия файла ключей %s для записи\n", key_filename);
        return;
    }
    
    FILE *value_file = fopen(value_filename, "w");
    if (!value_file) {
        printf("Ошибка открытия файла значений %s для записи\n", value_filename);
        fclose(key_file);

        return;
    }
    
    for (int i = 0; i < table -> count; i++) {
        fprintf(key_file, "%s\n", table -> keys[i]);
        fprintf(value_file, "%s\n", table -> values[i]);
    }
    
    fclose(key_file);
    fclose(value_file);
}

int binarySearch(Table *table, int start, int end, const char *key, int current_index) {
    if (end <= start) {
        comparison_count++;
        
        int cmp = strcmp(key, table -> keys[start]);
        if (cmp > 0) return start + 1;
        if (cmp < 0) return start;
        
        return start + 1;
    }
    
    int mid = (start + end) / 2;
    
    comparison_count++;
    
    int cmp = strcmp(key, table -> keys[mid]);
    if (cmp == 0) {
        return binarySearch(table, mid + 1, end, key, current_index);
    }
    
    comparison_count++;
    if (cmp > 0)
        return binarySearch(table, mid + 1, end, key, current_index);
    
    return binarySearch(table, start, mid - 1, key, current_index);
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
        
        int location = binarySearch(table, 0, j, key, i);
        
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

void searchByKey(Table *table, const char *key) {
    int left = 0;
    int right = table -> count - 1;
    int found_index = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(key, table -> keys[mid]);
        
        if (cmp == 0) {
            found_index = mid;
            break;
        }
        
        if (cmp > 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    if (found_index == -1) {
        printf("\nПоиск по ключу '%s': не найдено\n", key);
        return;
    }
    
    int start = found_index;
    int end = found_index;
    
    while (start > 0 && strcmp(table -> keys[start - 1], key) == 0)
        start--;
    
    while (end < table -> count - 1 && strcmp(table -> keys[end + 1], key) == 0)
        end++;
    
    int count = end - start + 1;
    printf("\nПоиск по ключу '%s': найдено %d вхождений:\n", key, count);
    
    for (int i = start; i <= end; i++)
        printf("Позиция %d: значение %s\n", i + 1, table -> values[i]);
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
    
    if (argc < 2 || !strcmp(argv[1], KEY_HELP)) {
        printHelp();
        return 0;
    }
    
    char *input_file = NULL;
    int tail_lines = 0;
    int show_stats = 0;
    int quiet_mode = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], KEY_TAIL) == 0) {
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

        return 0;
    }
    
    Table table;
    int count;
    
    count = readData(input_file, &table);
    if (!count) {
        printf("Не удалось прочитать данные из файла %s\n", input_file);
        return 0;
    }
            
    binaryInsertionSort(&table);
    
    writeData("output.txt", &table);
    
    if (show_stats)
        printStats();
    
    if (quiet_mode) {
        printf("\nТаблица отсортирована и записана в папку output.\n");
        return 0;
    }

    printTable(&table, tail_lines);

    printf("Введите ключи для поиска:\n\n");
    char input_buffer[MAX_STRING_LENGTH];
    
    while (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        input_buffer[strcspn(input_buffer, "\n")] = '\0';
        
        if (!strlen(input_buffer))
            continue;
        
        char *token = strtok(input_buffer, " ");
        while (token != NULL) {
            if (strlen(token) > KEY_LENGTH)
                printf("\nПредупреждение: ключ '%s' длиннее %d знаков\n", token, KEY_LENGTH);
            else 
                searchByKey(&table, token);
            
            token = strtok(NULL, " ");
        }

        printf("\n");
    }
    
    printf("\nПоиск завершён.\n");
}
