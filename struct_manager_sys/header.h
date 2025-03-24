#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

#define MaxStringSize 200 // Максимальная длинна строки
#define DefMaxRow 10      // Максимальное количество строк по умолчанию
#define DefMaxColumns 5   // Максимальное количество полей по умолчанию
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
struct blockbase
{
    table *tables[MaxTables];
    int tableCount;
    char *nameDb;
    int dbCount;
};

char *login(char **usersList);

void start(blockbase *db, char *user);

int enterEl();

blockbase *loadDbInFile(blockbase *db);

table *mem(char *tableName, char *columns, int isLoad);

void enterStruct(blockbase *db);

void printStruct(blockbase *db, int position);

int againProg();