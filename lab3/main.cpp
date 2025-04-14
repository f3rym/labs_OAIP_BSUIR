#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1, result;
    char expression[K];
    while (again)
    {
        printf("Введите выражение: ");
        rewind(stdin);
        fgets(expression, K, stdin);
        result = checkExpression(expression);
        printIsCorrect(result);
        again = againProg();
    }
    return 0;
}