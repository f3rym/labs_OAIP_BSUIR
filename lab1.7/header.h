#pragma once

struct cubeProperties
{
    int size;
    char* color;
    char* materials;
};


int enterM();

struct cubeProperties *memStruct(int m, int K);

void enterCubeProperties(cubeProperties *cube, int m, int K);

void printCubeProperties(cubeProperties *cube, int m);

void AfindVolumeCube(cubeProperties *cube, int m);

void BfindSizeCube(cubeProperties *cube, int l);

int againProg();
