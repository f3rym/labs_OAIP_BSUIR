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

int enterN()
{
    int el, y;
    while (1)
    {
        printf("Введите длину ребра куба, которую мы ищем:\t");
        y = scanf_s("%d", &el);
        if (CheckElement(el, y))
            break;
    };
    return el;
}

int enterEl()
{
    int el, y;
    while (1)
    {
        y = scanf_s("%d", &el);
        if (CheckElement(el, y))
            break;
    };
    return el;
}

struct cubeProperties *mem(int m, int K)
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
        printf("\nВведите характеристики куба номер %d:\n", i + 1);
        while (1)
        {
            printf("\nВведите длину куба(в см.):\t");
            int y = scanf_s("%d", &(cube + i)->size);
            if (CheckElement((cube + i)->size, y))
                break;
        }
        printf("\nВведите цвет кубика из предложенных(\033[36mred, yellow, green or blue\033[0m):\t");
        rewind(stdin);
        fgets((cube + i)->color, K, stdin);
        for (int k = 0; k < strlen((cube + i)->color); k++)
            if (*((cube + i)->color + k) == '\n')
                *((cube + i)->color + k) = '\0';
        printf("\nВведите материал кубика из предложенных(\033[36mwood, metal or cardboard\033[0m):\t");
        rewind(stdin);
        fgets((cube + i)->materials, K, stdin);
        for (int k = 0; k < strlen((cube + i)->materials); k++)
            if (*((cube + i)->materials + k) == '\n')
                *((cube + i)->materials + k) = '\0';
    }
}

void AfindVolumeCube(cubeProperties *cube, int m)
{
    int CountRed = 0, CountYellow = 0, CountGreen = 0, CountBlue = 0, CountWood = 0, CountMetal = 0;
    int VolumeRed = 0, VolumeYellow = 0, VolumeGreen = 0, VolumeBlue = 0;
    for (int i = 0; i < m; i++)
    {
        if (strcmp((cube + i)->color, "red") == 0)
        {
            CountRed++;
            VolumeRed += (cube + i)->size * (cube + i)->size * (cube + i)->size;
        }
        else if (strcmp((cube + i)->color, "yellow") == 0)
        {
            CountYellow++;
            VolumeYellow += (cube + i)->size * (cube + i)->size * (cube + i)->size;
        }
        else if (strcmp((cube + i)->color, "green") == 0)
        {
            CountGreen++;
            VolumeGreen += (cube + i)->size * (cube + i)->size * (cube + i)->size;
        }
        else
        {
            CountBlue++;
            VolumeBlue += (cube + i)->size * (cube + i)->size * (cube + i)->size;
        }
    }
    printf("=== Цвет ======= Объем(cm^3.) ====  Количество  ===============================\n");
    printf("| %-10s | %-15d | %-15d |\n", "Red", VolumeRed, CountRed);
    printf("| %-10s | %-15d | %-15d |\n", "Yellow", VolumeYellow, CountYellow);
    printf("| %-10s | %-15d | %-15d |\n", "Green", VolumeGreen, CountGreen);
    printf("| %-10s | %-15d | %-15d |\n", "Blue", VolumeBlue, CountBlue);
    printf("================================================================================\n");
}

void printCubeProperties(cubeProperties *cube, int m)
{
    printf("\nХарактеристики кубов:\n");
    printf("\n===== № ====== Длинна ребра(cm.) ======== Цвет ========= Материал ==============\n");
    for (int i = 0; i < m; i++)
        printf("|     %-2d     |     %-10d     | %-15s | %-15s |\n", i + 1, (cube + i)->size, (cube + i)->color, (cube + i)->materials);
}

void BfindSizeCube(cubeProperties *cube, int l)
{
    int CountWood = 0, CountMetal = 0;
    int n, m;
    printf("\nВведите длину ребра n деревянного кубика (в cm.):\t");
    n = enterEl();
    printf("\nВведите от какой длины m ребра металлического кубика (в cm.):\t");
    m = enterEl();
    for (int i = 0; i < l; i++)
    {
        if (strcmp((cube + i)->materials, "wood") == 0 && (cube + i)->size == n)
            CountWood++;
        else if (strcmp((cube + i)->materials, "metal") == 0 && (cube + i)->size > m)
            CountMetal++;
    }
    printf("\n== Материал == Длина ребра(cm.) ==  Количество  ==============================\n");
    printf("| %-10s | %-15d | %-15d |\n", "Wood", n, CountWood);
    printf("| %-10s | >%-14d | %-15d |\n", "Metal", m, CountMetal);
    printf("================================================================================\n");
}

void poisk(cubeProperties *cube, int m, int K, int n)
{
    // Выделение памяти под новую структуру
    cubePoisk *poisk;
    int CountPoisk = 0, k = 0;
    poisk = (struct cubePoisk *)calloc(m, sizeof(cubePoisk));
    if (!poisk)
    {
        printf("Память не была выделена :(\n");
    }
    for (int i = 0; i < m; i++)
    {
        (poisk + i)->materials = (char *)calloc(K, sizeof(char));
        (poisk + i)->color = (char *)calloc(K, sizeof(char));
        if (!(poisk + i)->color || !(poisk + i)->materials)
        {
            printf("Ошибка выделения памяти для строк.\n");
        }
    }
    // Заполняем структуру
    for (int i = 0; i < m; i++)
    {
        if ((cube + i)->size == n)
        {
            (poisk + k)->size = (cube + i)->size;
            (poisk + k)->color = (cube + i)->color;
            (poisk + k)->materials = (cube + i)->materials;
            k++;
            CountPoisk++;
        }
    }
    poisk = (struct cubePoisk *)realloc(poisk, CountPoisk * sizeof(cubePoisk));
    if (!poisk)
        printf("Ошибка при перезаписи памяти.\n");
    printf("\nХарактеристики кубов:\n");
    printf("\n===== № ====== Длинна ребра(cm.) ======== Цвет ========= Материал ==============\n");
    for (int i = 0; i < m; i++)
        printf("|     %-2d     |     %-10d     | %-15s | %-15s |\n", i + 1, (poisk + i)->size, (poisk + i)->color, (poisk + i)->materials);
    for (int i = 0; i < CountPoisk; i++)
    {
        free((poisk + i)->color);
        free((poisk + i)->materials);
    }
    free(poisk);
}

void freeCubeMemory(cubeProperties *cube, int m)
{
    for (int i = 0; i < m; i++)
    {
        free((cube + i)->color);
        free((cube + i)->materials);
    }
    free(cube);
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