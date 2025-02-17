#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MaxStringSize 50 // Максимальная длинна строки
#define DefMaxRow 5      // Максимальное количество строк по умолчанию
#define DefMaxColumns 4  // Максимальное количество полей по умолчанию
#define MaxTables 10      // Максимальное количество таблиц
struct table
{
    char **valColumns;
    char ***valRow;
    char *nameTb;
    int columnsCount;
    int rowCount;
    int maxRow;
};
struct database
{
    table *tables[MaxTables];
    int tableCount;
    char *nameDb;
    int dbCount;
};


void start(database *db);

int enterEl();

// database *createDB();

table *mem(char *tableName, char *columns);

void enterStruct(database *db);

void printStruct(database *db, int position);

int againProg();