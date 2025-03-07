#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

union infoStudent
{
    int inMinsk;
    int inVillage;
    int regionMinsk;
    char *region;
    char *city;
    char *district;
    char *street;
    char *house;
    int flat;
};

int enterM();

int enterN();

int againProg();
