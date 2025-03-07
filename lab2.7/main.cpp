#include "header.h"

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
