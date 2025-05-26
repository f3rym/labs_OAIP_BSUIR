#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1, m, type = 0;
    infoStudent *students = NULL;
    while (again)
    {
        printf("Введите кол-во студентов:\t");
        m = enterEl();
        students = mem(m);
        enterStudentsAddress(students, m);
        cyclePrintStudentsAddress(students, type, m);
        freeMemory(students, m);
        again = againProg();
    }
    return 0;
}
   