#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Устанавливаем только кодировку
    int again = 1, columns, choice;
    table *def;
    database *db;
    while (again)
    {
        printf("\033[1;36mДобро пожаловать в feSQL!\033[0m\n");                           
        printf("\033[1;32mВведите команду или введите /help\033[0m :\n"); 
        start(db);
        again = againProg();
    }
}