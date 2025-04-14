#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define K 80

struct Node 
{
    char carNumber[K];
    struct Node *next;
    struct Node *prev;
};

struct linkedList
{
    Node* head;
    Node* tail;
    int countCars;
};

struct infoParking
{
    int countPlace;
    linkedList *list;
};



int enterEl();


struct infoParking *mem(int countParkingLot);

void enterInfoParking(infoParking *parking, int countParkingLot);

void managerInfoCars(infoParking **parking, int *countParkingLot);

void memClear(infoParking *parking, int countParkingLot); 

int againProg();
