#include "header.h"

stack *push(stack *s, char c)
{
    stack *s1;
    s1 = (stack *)malloc(sizeof(stack));
    if (!s1)
        return NULL;
    s1->inf = c;
    s1->next = s;
    return s1;
}

int pop1(stack **s, char *last)
{
    stack *s1 = *s;
    *last = s1->inf;
    *s = s1->next;
    free(s1);
    return 1;
}

void memClear(stack *s)
{
    while (s != NULL)
    {
        stack *s1 = s;
        s = s->next;
        free(s1);
    }
}

int isOpenBracket(char c)
{
    if (c == '(' || c == '[' || c == '{')
        return 1;
    return 0;
}

int isCloseBracket(char c)
{
    if (c == ']' || c == '}' || c == ')')
        return 1;
    return 0;
}

int isMatchingPair(char last, char s)
{
    if ((last == '(' && s == ')') || (last == '[' && s == ']') || (last == '{' && s == '}'))
        return 1;
    return 0;
}

int checkExpression(char *expression)
{
    stack *s = NULL;
    char last;
    int len = strlen(expression);
    for (int i = 0; i < len; i++)
    {
        char c = *(expression + i);
        if (isOpenBracket(c))
            s = push(s, c);
        else if (isCloseBracket(c))
        {
            if (s == NULL)
                return i;
            pop1(&s, &last);
            if (!isMatchingPair(last, c))
            {
                memClear(s);
                return i;
            }
        }
    }
    if (s != NULL)
    {
        int error_pos = len - 2;
        memClear(s);
        return error_pos;
    }
    memClear(s);
    return -1;
}

void printIsCorrect(int result)
{
    if (result == -1)
        printf("\033[1;36mВыражение корректно\033[0m");
    else
        printf("\033[1;31mОшибка в позиции \033[1;34m%d\033[1;31m: несоответствие скобок\033[0m", result + 1);
}
