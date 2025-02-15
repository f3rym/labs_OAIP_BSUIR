#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CheckElement(int a, int y)
{
    if (y != 1 || a <= 0 || a >= INT_MAX)
    {
        printf("\n\033[31mОшибка. Введено не число или оно > %d. Попробуй снова.\033[0m\n\n", INT_MAX);
        rewind(stdin);
        return 0;
    }
    else
        return 1;
}

int enterM()
{
    int el, y;
    while (1)
    {
        printf("Введите кол-во\033[33m кубиков\033[0m m :\t");
        y = scanf_s("%d", &el);
        if (CheckElement(el, y))
            break;
    };
    return el;
}

struct cubeProperties *memStruct(int m, int K)
{
    cubeProperties *cube;
    cube = (struct cubeProperties *)calloc(m, sizeof(cubeProperties));
    if (!cube)
    {
        printf("Память не была выделена :(\n");
        return NULL;
    }
    for (int i = 0; i < m; i++)
    {
        (cube + i)->materials = (char *)calloc(K, sizeof(char));
        (cube + i)->color = (char *)calloc(K, sizeof(char));
        if (!(cube + i)->color || !(cube + i)->materials)
        {
            printf("Ошибка выделения памяти для строк.\n");
            return NULL;
        }
    }
    return cube;
}

void enterCubeProperties(cubeProperties *cube, int m, int K)
{
    for (int i = 0; i < m; i++)
    {
        printf("Введите характеристики куба номер %d:\n", i + 1);
        while (1)
        {
            printf("Введите длину куба:\t");
            int y = scanf_s("%d", &(cube + i)->size);
            if (CheckElement((cube + i)->size, y))
                break;
        }
        printf("Введите цвет кубика или выберете из предложенных(\033[36mred, yellow, green or blue\033[0m):\t");
        rewind(stdin);
        fgets((cube + i)->color, K, stdin);
        for (int k = 0; k < sizeof((cube + i)->color); k++)
            if (*((cube + i)->color+k) == '\n')
                *((cube + i)->color+k) = '\0';
        printf("Введите материал кубика или выберете из предложенных(\033[36mwood, metal or cardboard\033[0m):\t");
        rewind(stdin);
        fgets((cube + i)->materials, K, stdin);
        for (int k = 0; k < sizeof((cube + i)->materials); k++)
            if (*((cube + i)->materials + k) == '\n')
                *((cube + i)->materials + k) = '\0';
    }
}

void printCubeProperties(cubeProperties *cube, int m)
{
    printf("Характеристики кубов:\n");
    printf("===== № ======== Длинна ребра ============== Цвет ========= Материал ======\n");
    for (int i = 0; i < m; i++)
    {
        printf("|     %-2d     |     %-10d     | %-15s | %-15s |\n",
               i + 1,                  // Номер куба
               (cube + i)->size,       // Длина ребра
               (cube + i)->color,      // Цвет
               (cube + i)->materials); // Материал
    }
    printf("===========================================================================\n");
}

int againProg()
{
    int y, again;
    printf("\nХотите попробовать снова? \033[32mДа - 1\033[0m. \033[31mНет - 0 \033[0m:\t");
    while (1)
    {
        y = scanf_s("%d", &again);
        if (y != 1 || (again != 0 && again != 1))
        {
            printf("\033[31mОшибка. Переход к завершению...\033[0m");
            rewind(stdin);
            again = 0;
            return again;
        }
        else
            break;
    }
    return again;
}
