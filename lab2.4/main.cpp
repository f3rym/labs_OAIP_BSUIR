#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1, m, type = 0;
    infoStudent *students = NULL;
    // Указатель на функцию для вывода информации о студентах
    void (*funcPtr)(infoStudent *, int, int) = printStudentsAddress;
    while (again)
    {
        printf("Введите кол-во студентов:\t");
        m = enterEl();
        students = mem(m);
        enterStudentsAddress(students, m);
        while(type > -1 && type < 4)
        {
            printf("Выберите номер типа для вывода (0 - минчанин, 1 - в минской области, 2 - иногородний, 3 - из деревни), или иное для выхода: ");
            type = enterEl();
            funcPtr(students, m, type);
        }    
        freeMemory(students, m);       
        again = againProg();
    }

    return 0;
}
