#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_STRING_LENGTH 256
#define MAX_RECORDS 1000

typedef struct {
    char key[6];
    char value[MAX_STRING_LENGTH];
} Record;

void swap(Record *a, Record *b) {
    Record temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(Record *array, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&array[i], &array[j]);
    }
}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    if (argc != 3) {
        printf("Использование: %s <входной_файл> <выходной_файл>\n", argv[0]);
        return 1;
    }

    Record records[MAX_RECORDS];
    int count = 0;

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Ошибка открытия входного файла\n");
        return 1;
    }

    char line[MAX_STRING_LENGTH * 2];
    while (count < MAX_RECORDS && fgets(line, sizeof(line), input)) {
        char *key = strtok(line, " \n");
        char *value = strtok(NULL, "\n");
        if (key && value) {
            strncpy(records[count].key, key, 5);
            records[count].key[5] = '\0';
            strcpy(records[count].value, value);
            count++;
        }
    }
    fclose(input);

    shuffle(records, count);

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        printf("Ошибка открытия выходного файла\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(output, "%s %s\n", records[i].key, records[i].value);
    }
    fclose(output);

    printf("Данные успешно перемешаны и записаны в %s\n", argv[2]);
} 