#include "header.h"

struct infoStudent *mem(int m)
{
    infoStudent *students;
    students = (infoStudent *)calloc(m, sizeof(infoStudent));
    if (!students)
    {
        printf("Память не была выделена :(\n");
        return NULL;
    }
    for (int i = 0; i < m; i++)
    {
        (students + i)->fio = (char *)malloc(K * sizeof(char));
        if (!(students + i)->fio)
        {
            printf("Ошибка выделения памяти для строк.\n");
            return NULL;
        }
    }
    return students;
}

struct infoStudentPoisk *memPoisk(int m)
{
    infoStudentPoisk *students;
    students = (infoStudentPoisk *)calloc(m, sizeof(infoStudentPoisk));
    if (!students)
    {
        printf("Память не была выделена :(\n");
        return NULL;
    }
    for (int i = 0; i < m; i++)
    {
        (students + i)->fio = (char *)malloc(K * sizeof(char));
        if (!(students + i)->fio)
        {
            printf("Ошибка выделения памяти для строк.\n");
            return NULL;
        }
    }
    return students;
}

void memUnion(infoStudent *students, int i)
{
    if ((students + i)->isLocale == 0)
    {
        (students + i)->address.Minsk.street = (char *)malloc(K * sizeof(char));
    }
    else if ((students + i)->isLocale == 1)
    {
        (students + i)->address.MinskRegion.city = (char *)malloc(K * sizeof(char));
        (students + i)->address.MinskRegion.street = (char *)malloc(K * sizeof(char));
    }
    else if ((students + i)->isLocale == 2)
    {
        (students + i)->address.outMinskRegion.region = (char *)malloc(K * sizeof(char));
        (students + i)->address.outMinskRegion.district = (char *)malloc(K * sizeof(char));
        (students + i)->address.outMinskRegion.city = (char *)malloc(K * sizeof(char));
        (students + i)->address.outMinskRegion.street = (char *)malloc(K * sizeof(char));
    }
    else if ((students + i)->isLocale == 3)
    {
        (students + i)->address.Village.region = (char *)malloc(K * sizeof(char));
        (students + i)->address.Village.district = (char *)malloc(K * sizeof(char));
        (students + i)->address.Village.village = (char *)malloc(K * sizeof(char));
    }
}

void memUnionPoisk(infoStudentPoisk *studentsPoisk, int i)
{
    if ((studentsPoisk + i)->isLocale == 0)
    {
        (studentsPoisk + i)->address.Minsk.street = (char *)malloc(K * sizeof(char));
    }
    else if ((studentsPoisk + i)->isLocale == 1)
    {
        (studentsPoisk + i)->address.MinskRegion.city = (char *)malloc(K * sizeof(char));
        (studentsPoisk + i)->address.MinskRegion.street = (char *)malloc(K * sizeof(char));
    }
    else if ((studentsPoisk + i)->isLocale == 2)
    {
        (studentsPoisk + i)->address.outMinskRegion.region = (char *)malloc(K * sizeof(char));
        (studentsPoisk + i)->address.outMinskRegion.district = (char *)malloc(K * sizeof(char));
        (studentsPoisk + i)->address.outMinskRegion.city = (char *)malloc(K * sizeof(char));
        (studentsPoisk + i)->address.outMinskRegion.street = (char *)malloc(K * sizeof(char));
    }
    else if ((studentsPoisk + i)->isLocale == 3)
    {
        (studentsPoisk + i)->address.Village.region = (char *)malloc(K * sizeof(char));
        (studentsPoisk + i)->address.Village.district = (char *)malloc(K * sizeof(char));
        (studentsPoisk + i)->address.Village.village = (char *)malloc(K * sizeof(char));
    }
}

void enterStudentsAddress(infoStudent *students, int m)
{
    printf("Введите данные о студентах.\n");
    for (int i = 0; i < m; i++)
    {
        printf("\nВведите ФИО студента:\t");
        rewind(stdin);
        fgets((students + i)->fio, K, stdin);
        (students + i)->fio[strcspn((students + i)->fio, "\n")] = '\0';
        printf("Введите (0 - минчанин, 1 - в минской области, 2 - иногородний, 3 - из деревни) :\t");
        (students + i)->isLocale = enterEl();
        printf("\nВведите данные о адресе студента.\n\n");
        if ((students + i)->isLocale == 0)
        {
            printf("Введите улицу студента:\t");
            rewind(stdin);
            memUnion(students, i);
            fgets((students + i)->address.Minsk.street, K, stdin);
            (students + i)->address.Minsk.street[strcspn((students + i)->address.Minsk.street, "\n")] = '\0';
            printf("Введите номер дома студента:\t");
            (students + i)->address.Minsk.house = enterEl();
            printf("Введите номер квартиры студента:\t");
            (students + i)->address.Minsk.flat = enterEl();
        }
        else if ((students + i)->isLocale == 1)
        {
            printf("Введите город студента:\t");
            rewind(stdin);
            memUnion(students, i);
            fgets((students + i)->address.MinskRegion.city, K, stdin);
            (students + i)->address.MinskRegion.city[strcspn((students + i)->address.MinskRegion.city, "\n")] = '\0';
            printf("Введите улицу студента:\t");
            rewind(stdin);
            fgets((students + i)->address.MinskRegion.street, K, stdin);
            (students + i)->address.MinskRegion.street[strcspn((students + i)->address.MinskRegion.street, "\n")] = '\0';
            printf("Введите номер дома студента:\t");
            (students + i)->address.MinskRegion.house = enterEl();
            printf("Введите номер квартиры студента:\t");
            (students + i)->address.MinskRegion.flat = enterEl();
        }
        else if ((students + i)->isLocale == 2)
        {
            printf("Введите область студента:\t");
            rewind(stdin);
            memUnion(students, i);
            fgets((students + i)->address.outMinskRegion.region, K, stdin);
            (students + i)->address.outMinskRegion.region[strcspn((students + i)->address.outMinskRegion.region, "\n")] = '\0';
            printf("Введите район студента:\t");
            rewind(stdin);
            fgets((students + i)->address.outMinskRegion.district, K, stdin);
            (students + i)->address.outMinskRegion.district[strcspn((students + i)->address.outMinskRegion.district, "\n")] = '\0';
            printf("Введите город студента:\t");
            rewind(stdin);
            fgets((students + i)->address.outMinskRegion.city, K, stdin);
            (students + i)->address.outMinskRegion.city[strcspn((students + i)->address.outMinskRegion.city, "\n")] = '\0';
            printf("Введите улицу студента:\t");
            rewind(stdin);
            fgets((students + i)->address.outMinskRegion.street, K, stdin);
            (students + i)->address.outMinskRegion.street[strcspn((students + i)->address.outMinskRegion.street, "\n")] = '\0';
            printf("Введите номер дома студента:\t");
            (students + i)->address.outMinskRegion.house = enterEl();
            printf("Введите номер квартиры студента:\t");
            (students + i)->address.outMinskRegion.flat = enterEl();
        }
        else if ((students + i)->isLocale == 3)
        {
            printf("Введите регион студента:\t");
            rewind(stdin);
            memUnion(students, i);
            fgets((students + i)->address.Village.region, K, stdin);
            (students + i)->address.Village.region[strcspn((students + i)->address.Village.region, "\n")] = '\0';
            printf("Введите область студента:\t");
            rewind(stdin);
            fgets((students + i)->address.Village.district, K, stdin);
            (students + i)->address.Village.district[strcspn((students + i)->address.Village.district, "\n")] = '\0';
            printf("Введите название деревни студента:\t");
            rewind(stdin);
            fgets((students + i)->address.Village.village, K, stdin);
            (students + i)->address.Village.village[strcspn((students + i)->address.Village.village, "\n")] = '\0';
            printf("Введите номер дома студента:\t");
            (students + i)->address.Village.house = enterEl();
        }
        else
        {
            printf("Данного типа студента не существует\n");
            continue;
        }
    }
}




void memClearPoisk(infoStudentPoisk *studentsPoisk, int m)
{
    for (int i = 0; i < m; i++)
    {
        free((studentsPoisk + i)->fio);
        switch ((studentsPoisk + i)->isLocale)
        {
        case 0:
            free((studentsPoisk + i)->address.Minsk.street);
            break;
        case 1:
            free((studentsPoisk + i)->address.MinskRegion.city);
            free((studentsPoisk + i)->address.MinskRegion.street);
            break;
        case 2:
            free((studentsPoisk + i)->address.outMinskRegion.region);
            free((studentsPoisk + i)->address.outMinskRegion.district);
            free((studentsPoisk + i)->address.outMinskRegion.city);
            free((studentsPoisk + i)->address.outMinskRegion.street);
            break;
        case 3:
            free((studentsPoisk + i)->address.Village.region);
            free((studentsPoisk + i)->address.Village.district);
            free((studentsPoisk + i)->address.Village.village);
            break;
        default:
            break;
        }
    }
    free(studentsPoisk);
}

void studentsFind(infoStudent *students, infoStudentPoisk **studentsPoisk, int type, int m, int *countStudents)
{
    int j = 0;
    *countStudents = 0;
    *studentsPoisk = memPoisk(m);

    if (type == 0)
    {
        for (int i = 0; i < m; i++)
        {
            if ((students + i)->isLocale == 0)
            {
                (*studentsPoisk + j)->isLocale = (students + i)->isLocale;
                memUnionPoisk(*studentsPoisk, j);
                strcpy((*studentsPoisk + j)->fio, (students + i)->fio);
                strcpy((*studentsPoisk + j)->address.Minsk.street, (students + i)->address.Minsk.street);
                (*studentsPoisk + j)->address.Minsk.house = (students + i)->address.Minsk.house;
                (*studentsPoisk + j)->address.Minsk.flat = (students + i)->address.Minsk.flat;
                j++;
                (*countStudents)++;
            }
        }
        *studentsPoisk = (infoStudentPoisk *)realloc(*studentsPoisk, *countStudents * sizeof(infoStudentPoisk));
    }
    else if (type == 1)
    {
        j = 0;
        for (int i = 0; i < m; i++)
        {
            if ((students + i)->isLocale == 1)
            {

                (*studentsPoisk + j)->isLocale = (students + i)->isLocale;
                memUnionPoisk(*studentsPoisk, j);
                strcpy((*studentsPoisk + j)->fio, (students + i)->fio);
                strcpy((*studentsPoisk + j)->address.MinskRegion.city, (students + i)->address.MinskRegion.city);
                strcpy((*studentsPoisk + j)->address.MinskRegion.street, (students + i)->address.MinskRegion.street);
                (*studentsPoisk + j)->address.MinskRegion.house = (students + i)->address.MinskRegion.house;
                (*studentsPoisk + j)->address.MinskRegion.flat = (students + i)->address.MinskRegion.flat;
                j++;
                (*countStudents)++;
            }
        }
        *studentsPoisk = (infoStudentPoisk *)realloc(*studentsPoisk, *countStudents * sizeof(infoStudentPoisk));
    }
    else if (type == 2)
    {
        j = 0;
        for (int i = 0; i < m; i++)
        {
            if ((students + i)->isLocale == 2)
            {
                (*studentsPoisk + j)->isLocale = (students + i)->isLocale;
                memUnionPoisk(*studentsPoisk, j);
                strcpy((*studentsPoisk + j)->fio, (students + i)->fio);
                strcpy((*studentsPoisk + j)->address.outMinskRegion.region, (students + i)->address.outMinskRegion.region);
                strcpy((*studentsPoisk + j)->address.outMinskRegion.city, (students + i)->address.outMinskRegion.city);
                strcpy((*studentsPoisk + j)->address.outMinskRegion.district, (students + i)->address.outMinskRegion.district);
                strcpy((*studentsPoisk + j)->address.outMinskRegion.street, (students + i)->address.outMinskRegion.street);
                (*studentsPoisk + j)->address.outMinskRegion.house = (students + i)->address.outMinskRegion.house;
                (*studentsPoisk + j)->address.outMinskRegion.flat = (students + i)->address.outMinskRegion.flat;
                j++;
                (*countStudents)++;
            }
        }
        *studentsPoisk = (infoStudentPoisk *)realloc(*studentsPoisk, *countStudents * sizeof(infoStudentPoisk));
    }
    else if (type == 3)
    {
        j = 0;
        for (int i = 0; i < m; i++)
        {
            if ((students + i)->isLocale == 3)
            {
                (*studentsPoisk + j)->isLocale = (students + i)->isLocale;
                memUnionPoisk(*studentsPoisk, j);
                strcpy((*studentsPoisk + j)->fio, (students + i)->fio);
                strcpy((*studentsPoisk + j)->address.Village.region, (students + i)->address.Village.region);
                strcpy((*studentsPoisk + j)->address.Village.district, (students + i)->address.Village.district);
                strcpy((*studentsPoisk + j)->address.Village.village, (students + i)->address.Village.village);
                (*studentsPoisk + j)->address.Village.house = (students + i)->address.Village.house;
                j++;
                (*countStudents)++;
            }
        }
        *studentsPoisk = (infoStudentPoisk *)realloc(*studentsPoisk, *countStudents * sizeof(infoStudentPoisk));
    }
}

void printStudentsAddress(infoStudent *students, int m, int type)
{
    int countStudents = 0;
    const char *defPlace[] = {"Минск", "Область", "Иногородние", "Из деревни"};
    if (type == 0)
    {
        infoStudentPoisk *studentsPoisk = NULL;
        studentsFind(students, &studentsPoisk, type, m, &countStudents);
        printf("\nСтуденты, проживающие в Минске\n\n");
        printf("=====================================================================================\n");
        printf("| %-3s | %-23s | %-15s | %-25s | %-8s | %-12s |\n", "N", "ФИО", "Тип адреса", "Улица", "Дом", "Квартира");
        printf("=====================================================================================\n");
        for (int i = 0; i < countStudents; i++)
        {
            printf("| %-3d | %-20s | %-15s | %-20s | %-5d | %-8d |\n",
                    i + 1,
                    (studentsPoisk + i)->fio,
                    defPlace[0],
                    (studentsPoisk + i)->address.Minsk.street,
                    (studentsPoisk + i)->address.Minsk.house,
                    (studentsPoisk + i)->address.Minsk.flat);
        }
        memClearPoisk(studentsPoisk, countStudents);
        printf("=====================================================================================\n");
    }
    else if (type == 1)
    {
        infoStudentPoisk *studentsPoisk = NULL;
        studentsFind(students, &studentsPoisk, type, m, &countStudents);
        printf("\nСтуденты, проживающие в Минской области\n\n");
        printf("=========================================================================================================\n");
        printf("| %-3s | %-20s | %-6s | %-25s | %-25s | %-8s | %-13s |\n", "N", "ФИО", "Тип адреса", "Город", "Улица", "Дом", "Квартира");
        printf("=========================================================================================================\n");
        for (int i = 0; i < countStudents; i++)
        {
            printf("| %-3d | %-17s | %-17s | %-20s | %-20s | %-5d | %-8d |\n",
                    i + 1,
                    (studentsPoisk + i)->fio,
                    defPlace[1],
                    (studentsPoisk + i)->address.MinskRegion.city,
                    (studentsPoisk + i)->address.MinskRegion.street,
                    (studentsPoisk + i)->address.MinskRegion.house,
                    (studentsPoisk + i)->address.MinskRegion.flat);
        }
        memClearPoisk(studentsPoisk, countStudents);
        printf("=========================================================================================================\n");
    }
    else if (type == 2)
    {
        infoStudentPoisk *studentsPoisk;
        studentsFind(students, &studentsPoisk, type, m, &countStudents);
        printf("\nИногородние студенты\n\n");
        printf("===========================================================================================================================================================\n");
        printf("| %-3s | %-23s | %-20s | %-27s | %-25s | %-25s | %-25s | %-8s | %-13s |\n",
                "N", "ФИО", "Тип адреса", "Область", "Район", "Город", "Улица", "Дом", "Квартира");
        printf("===========================================================================================================================================================\n");
        for (int i = 0; i < countStudents; i++)
        {
                printf("| %-3d | %-20s | %-18s | %-20s | %-20s | %-20s | %-20s | %-5d | %-8d |\n",
                        i + 1,
                        (studentsPoisk + i)->fio,
                        defPlace[2],
                        (studentsPoisk + i)->address.outMinskRegion.region,
                        (studentsPoisk + i)->address.outMinskRegion.district,
                        (studentsPoisk + i)->address.outMinskRegion.city,
                        (studentsPoisk + i)->address.outMinskRegion.street,
                        (studentsPoisk + i)->address.outMinskRegion.house,
                        (studentsPoisk + i)->address.outMinskRegion.flat);
        }
        memClearPoisk(studentsPoisk, countStudents);
        printf("===========================================================================================================================================================\n");
    }
    else if (type == 3)
    {
        infoStudentPoisk *studentsPoisk;
        studentsFind(students, &studentsPoisk, type, m, &countStudents);
        printf("\nСтуденты, проживающие в деревне\n\n");
        printf("=============================================================================================================================\n");
        printf("| %-3s | %-23s | %-15s | %-27s | %-25s | %-27s | %-13s |\n",
                "N", "ФИО", "Тип адреса", "Область", "Район", "Деревня", "Дом");
        printf("=============================================================================================================================\n");
        for (int i = 0; i < countStudents; i++)
        {
                printf("| %-3d | %-20s | %-15s | %-20s | %-20s | %-20s | %-10d |\n",
                        i + 1,
                        (studentsPoisk + i)->fio,
                        defPlace[3],
                        (studentsPoisk + i)->address.Village.region,
                        (studentsPoisk + i)->address.Village.district,
                        (studentsPoisk + i)->address.Village.village,
                        (studentsPoisk + i)->address.Village.house);
        }
        printf("=============================================================================================================================\n");
        memClearPoisk(studentsPoisk, countStudents);
    }
}

void cyclePrintStudentsAddress(infoStudent *students, int type, int m)
{
    void (*funcPtr)(infoStudent *, int, int) = printStudentsAddress;
    while (type > -1 && type < 4)
    {
        printf("Выберите номер типа для вывода (0 - минчанин, 1 - в минской области, 2 - иногородний, 3 - из деревни), или иное для выхода: ");
        type = enterEl();
        funcPtr(students, m, type);
    }
}

void freeMemory(infoStudent *students, int m)
{
    for (int i = 0; i < m; i++)
    {
        free((students + i)->fio);
        switch ((students + i)->isLocale)
        {
        case 0:
            free((students + i)->address.Minsk.street);
            break;
        case 1:
            free((students + i)->address.MinskRegion.city);
            free((students + i)->address.MinskRegion.street);
            break;
        case 2:
            free((students + i)->address.outMinskRegion.region);
            free((students + i)->address.outMinskRegion.district);
            free((students + i)->address.outMinskRegion.city);
            free((students + i)->address.outMinskRegion.street);
            break;
        case 3:
            free((students + i)->address.Village.region);
            free((students + i)->address.Village.district);
            free((students + i)->address.Village.village);
            break;
        default:
            break;
        }
    }
    free(students);
}

// g++ main.cpp myf.cpp mylib.cpp -o main && ./main