#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define K 50

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1, m, n;
    cubeProperties *cube;
    cubePoisk *cubePoisk;
    while (again)
    {
        m = enterM();
        cube = mem(m, K);
        enterCubeProperties(cube, m, K);
        printCubeProperties(cube, m);
        AfindVolumeCube(cube, m);
        BfindSizeCube(cube, m);
        n = enterN();
        poisk(cube, m, K, n);
        freeCubeMemory(cube, m);
        again = againProg();
    }
}
/*
Лабораторная работа № 1.7
Имеются сведения о кубиках: размер каждого кубика(длина ребра в сантиметрах), его цвет (красный, желтый, зеленый и синий) и материал(дерево, металл, картон). Найти: 
а) количество кубиков каждого из перечисленных цветов и их суммарный объем;
б) количество деревянных кубиков с ребром n сантиметров и количество металлических кубиков с ребром большим m сантиметров.
*/