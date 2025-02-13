#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1;
    int m;
    while(again)
    {
        m = enterM();
        cubeProperties *cube = createStruct(m);
        enterCubeProperties(cube, m);
        printCubeProperties(cube, m);
        free(cube);
        again = againProg();
    }
}