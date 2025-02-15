#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define K 50

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1, m;
    while (again)
    {
        m = enterM();
        cubeProperties *cube = memStruct(m, K);
        enterCubeProperties(cube, m, K);
        printCubeProperties(cube, m);
        AfindVolumeCube(cube, m);
        BfindSizeCube(cube, m);
        ///////// freeeeeeeeeeeeeeeeeeeeeeeeee
        free(cube);
        again = againProg();
    }
}