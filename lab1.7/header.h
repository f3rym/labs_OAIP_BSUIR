#pragma once

struct cubeProperties
{
    int size;
    char color[20];
    char materials[20];
};

int enterM();

struct cubeProperties *createStruct(int m);

void enterCubeProperties(cubeProperties *cube, int m);

void printCubeProperties(cubeProperties *cube, int m);

int againProg();
