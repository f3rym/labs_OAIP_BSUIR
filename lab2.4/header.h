#pragma once

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define K 80

struct inMinsk
{
    char *street;
    int house;
    int flat;
};
struct inMinskRegion
{
    char *city;
    char *street;
    int house;
    int flat;
};

struct outMinskRegion
{
    char *region;
    char *district;
    char *city;
    char *street;
    int house;
    int flat;
};

struct inVillage
{
    char *region;
    char *district;
    char *village;
    int house;
};
union address
{
    inMinsk Minsk;
    inMinskRegion MinskRegion;
    outMinskRegion outMinskRegion;
    inVillage Village;
};

struct infoStudent
{
    char *fio;
    int isLocale; // 0 - минчанин, 1 - в минской области, 2 - иногородней области, 3 - из деревни
    union address address;
};

struct infoStudentPoisk
{
    char *fio;
    int isLocale; // 0 - минчанин, 1 - в минской области, 2 - иногородней области, 3 - из деревни
    union address address;
};

int enterEl();

struct infoStudent* mem(int m);

void enterStudentsAddress(infoStudent *students, int m);

void cyclePrintStudentsAddress(infoStudent *students, int type, int m);

void freeMemory(infoStudent *students, int m);

int againProg();

