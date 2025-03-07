#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct cubeProperties
{
    int size;
    char* color;
    char* materials;
};

struct cubePoisk
{
    int size;
    char *color;
    char *materials;
};

int enterM();

int enterN();

struct cubeProperties *mem(int m, int K);

void enterCubeProperties(cubeProperties *cube, int m, int K);

void printCubeProperties(cubeProperties *cube, int m);

void AfindVolumeCube(cubeProperties *cube, int m);

void BfindSizeCube(cubeProperties *cube, int l);

void poisk(cubeProperties *cube, int m,  int K, int n);

void freeCubeMemory(cubeProperties *cube, int m);

int againProg();
