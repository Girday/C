#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STRING_LENGTH 256
#define MAX_RECORDS 1000
#define KEY_LENGTH 5
#define DEFAULT_TAIL_LINES 10

#define KEY_SEARCH "-s"    
#define KEY_TAIL "-t"      
#define KEY_STATS "-i"     
#define KEY_QUIET "-q"     
#define KEY_HELP "-h"      

typedef struct {
    char keys[MAX_RECORDS][KEY_LENGTH + 1];
    char values[MAX_RECORDS][MAX_STRING_LENGTH];
    int count;
} Table;

void setupConsole();
void printHelp();
int readData(const char *filename, Table *table);
void writeData(const char *filename, Table *table);
void printTable(Table *table, int lines);
void printStats();

int binarySearch(Table *table, int start, int end, const char *key);
void binaryInsertionSort(Table *table);
int searchByKey(Table *table, const char *key);

extern int comparison_count;
extern int movement_count;
