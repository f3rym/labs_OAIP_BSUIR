#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define K 80
struct infoStudent
{
    char *fio;
    int isLocale; // 0 - минчанин, 1 - в минской области, 2 - иногородней области, 3 - из деревни
    union address *address;
};
union address
{
    struct inMinsk
    {
        char *street;
        int house;
        int flat;
    } Minsk;
    struct inMinskRegion
    {
        char *city;
        char *street;
        int house;
        int flat;
    } MinskRegion;
    struct outMinskRegion
    {
        char *region;
        char *district;
        char *city;
        char *street;
        int house;
        int flat;
    } outMinskRegion;
    struct inVillage
    {
        char *region;
        char *district;
        char *village;
        int house;
    } Village;
};

int enterEl();

struct infoStudent* mem(int m);

void enterStudentsAddress(infoStudent *students, int m);

void printStudentsAddress(infoStudent *students, int m, int type);

void freeMemory(infoStudent *students, int m);

int againProg();

