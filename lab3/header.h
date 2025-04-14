#include <stdio.h>
#include <stdlib.h>
#include <locale.h.>
#include <string.h>

#define K 80

struct stack
{
    char inf;
    struct stack *next;
};

int checkExpression(char *expression);

void printIsCorrect(int result);

int againProg();
