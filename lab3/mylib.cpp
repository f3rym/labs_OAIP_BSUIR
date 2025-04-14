#include "header.h"

int CheckElement(int a, int y)
{
    if (y != 1 || a <= -1 || a >= INT_MAX)
    {
        printf("\n\033[31mОшибка. Введено не число или оно > %d. Попробуй снова.\033[0m\n\n", INT_MAX);
        rewind(stdin);
        return 0;
    }
    else
        return 1;
}

int enterEl()
{
    int el, y;
    while (1)
    {
        y = scanf_s("%d", &el);
        if (CheckElement(el, y))
            break;
    };
    return el;
}

int againProg()
{
    int y, again;
    printf("\nХотите попробовать снова? \033[32mДа - 1\033[0m. \033[31mНет - 0 \033[0m:\t");
    while (1)
    {
        y = scanf_s("%d", &again);
        if (y != 1 || (again != 0 && again != 1))
        {
            printf("\033[31mОшибка. Переход к завершению...\033[0m");
            rewind(stdin);
            again = 0;
            return again;
        }
        else
            break;
    }
    return again;
}