#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_STRING_LENGTH 256
#define MAX_RECORDS 1000
#define KEY_LENGTH 5

typedef struct {
    char keys[MAX_RECORDS][KEY_LENGTH + 1];
    char values[MAX_RECORDS][MAX_STRING_LENGTH];
    int count;
} Table;

void setupConsole();

int readData(const char *filename, Table *table);
void writeData(const char *filename, Table *table);
void printTable(Table *table);

int binarySearch(Table *table, int start, int end, const char *key);
void binaryInsertionSort(Table *table);
int searchByKey(Table *table, const char *key);
