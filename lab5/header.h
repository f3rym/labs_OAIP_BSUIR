#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Tree
{
    int key;
    struct Tree *left;
    struct Tree *right;
};

struct Tree *manageTree(Tree* root);

int enterEl();

void freeTree(Tree **root);

int againProg();
