#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Tree *root = NULL;
    int again = 1;
    while (again)
    {
        root = manageTree(root);
        freeTree(&root);
        printf("\nХотите ввести данные снова? \033[32mДа - 1\033[0m. \033[31mНет - 0 \033[0m:\t");
        again = againProg();
    }
    return 0;
}
