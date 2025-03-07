#include "header.h"


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

void printFindVolumeCube(int* colorCount, int* volumeCount)
{
    printf("=== Цвет ======= Объем(cm^3.) ====  Количество  ===============================\n");
    printf("| %-10s | %-15d | %-15d |\n", "red", *volumeCount, *colorCount);
    printf("| %-10s | %-15d | %-15d |\n", "yellow", *(volumeCount + 1), *(colorCount + 1));
    printf("| %-10s | %-15d | %-15d |\n", "green", *(volumeCount + 2), *(colorCount + 2));
    printf("| %-10s | %-15d | %-15d |\n", "blue", *(volumeCount + 3), *(colorCount + 3));
    printf("================================================================================\n");
}

void AfindVolumeCube(cubeProperties *cube, int m)
{
    int* colorCount, *volumeCount;
    colorCount = (int *)calloc(4, sizeof(int));
    volumeCount = (int *)calloc(4, sizeof(int));
    for (int i = 0; i < m; i++)
    {
        if (strcmp((cube + i)->color, "red") == 0)
        {
            (*colorCount)++;
            *volumeCount += (cube + i)->size * (cube + i)->size * (cube + i)->size;
        }
        else if (strcmp((cube + i)->color, "yellow") == 0)
        {
            (*(colorCount + 1))++;
            *(volumeCount + 1) += (cube + i)->size * (cube + i)->size * (cube + i)->size;
        }
        else if (strcmp((cube + i)->color, "green") == 0)
        {
            (*(colorCount + 2))++;
            *(volumeCount + 2) += (cube + i)->size * (cube + i)->size * (cube + i)->size;
        }
        else if (strcmp((cube + i)->color, "blue") == 0)
        {
            (*(colorCount + 3))++;
            *(volumeCount + 3) += (cube + i)->size * (cube + i)->size * (cube + i)->size;
        }
    }
    printFindVolumeCube(colorCount, volumeCount);
    free(colorCount);
    free(volumeCount);
}

void printCubeProperties(cubeProperties *cube, int m)
{
    printf("\nХарактеристики кубов:\n");
    printf("\n===== № ====== Длинна ребра(cm.) ======== Цвет ========= Материал ==============\n");
    for (int i = 0; i < m; i++)
        printf("|     %-2d     |     %-10d     | %-15s | %-15s |\n", i + 1, (cube + i)->size, (cube + i)->color, (cube + i)->materials);
}

void printFindSizeCube(int n, int m, int countWood, int countMetal)
{
    printf("\n== Материал == Длина ребра(cm.) ==  Количество  ==============================\n");
    printf("| %-10s | %-15d | %-15d |\n", "wood", n, countWood);
    printf("| %-10s | >%-14d | %-15d |\n", "metal", m, countMetal);
    printf("================================================================================\n");
}

void BfindSizeCube(cubeProperties *cube, int l)
{
    int countWood = 0, countMetal = 0;
    int n, m;
    printf("\nВведите длину ребра n деревянного кубика (в cm.):\t");
    n = enterEl();
    printf("\nВведите от какой длины m ребра металлического кубика (в cm.):\t");
    m = enterEl();
    for (int i = 0; i < l; i++)
    {
        if (strcmp((cube + i)->materials, "wood") == 0 && (cube + i)->size == n)
            countWood++;
        else if (strcmp((cube + i)->materials, "metal") == 0 && (cube + i)->size > m)
            countMetal++;
    }
    printFindSizeCube(n, m, countWood, countMetal);
}
void printPoisk(cubePoisk *poisk, int countPoisk)
{
    printf("\n===== № ====== Длинна ребра(cm.) ======== Цвет ========= Материал ==============\n");
    for (int i = 0; i < countPoisk; i++)
        printf("|     %-2d     |     %-10d     | %-15s | %-15s |\n", i + 1, (poisk + i)->size, (poisk + i)->color, (poisk + i)->materials);
    printf("==================================================================================\n");
}

void poisk(cubeProperties *cube, int m, int K, int n)
{
    // Выделение памяти под новую структуру
    cubePoisk *poisk;
    int countPoisk = 0, k = 0;
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
            strncpy((poisk + k)->color, (cube + i)->color, K);
            strncpy((poisk + k)->materials, (cube + i)->materials, K);
            k++;
            countPoisk++;
        }
    }
    poisk = (struct cubePoisk *)realloc(poisk, countPoisk * sizeof(cubePoisk));
    if (!poisk)
        printf("Ошибка при перезаписи памяти.\n");
    printPoisk(poisk, countPoisk);
    for (int i = 0; i < countPoisk; i++)
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