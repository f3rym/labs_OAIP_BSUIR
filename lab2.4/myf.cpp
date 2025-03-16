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
        (students + i)->address = (address *)malloc(sizeof(address));
        if (!(students + i)->fio || !(students + i)->address)
        {
            printf("Ошибка выделения памяти для строк.\n");
            return NULL;
        }
        (students + i)->address->Minsk.street = (char *)malloc(K * sizeof(char));
        (students + i)->address->MinskRegion.city = (char *)malloc(K * sizeof(char));
        (students + i)->address->MinskRegion.street = (char *)malloc(K * sizeof(char));
        (students + i)->address->outMinskRegion.region = (char *)malloc(K * sizeof(char));
        (students + i)->address->outMinskRegion.district = (char *)malloc(K * sizeof(char));
        (students + i)->address->outMinskRegion.city = (char *)malloc(K * sizeof(char));
        (students + i)->address->outMinskRegion.street = (char *)malloc(K * sizeof(char));
        (students + i)->address->Village.region = (char *)malloc(K * sizeof(char));
        (students + i)->address->Village.district = (char *)malloc(K * sizeof(char));
        (students + i)->address->Village.village = (char *)malloc(K * sizeof(char));
    }

    return students;
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
            fgets((students + i)->address->Minsk.street, K, stdin);
            (students + i)->address->Minsk.street[strcspn((students + i)->address->Minsk.street, "\n")] = '\0';
            printf("Введите номер дома студента:\t");
            (students + i)->address->Minsk.house = enterEl();
            printf("Введите номер квартиры студента:\t");
            (students + i)->address->Minsk.flat = enterEl();
        }
        else if ((students + i)->isLocale == 1)
        {
            printf("Введите город студента:\t");
            rewind(stdin);
            fgets((students + i)->address->MinskRegion.city, K, stdin);
            (students + i)->address->MinskRegion.city[strcspn((students + i)->address->MinskRegion.city, "\n")] = '\0';
            printf("Введите улицу студента:\t");
            rewind(stdin);
            fgets((students + i)->address->MinskRegion.street, K, stdin);
            (students + i)->address->MinskRegion.street[strcspn((students + i)->address->MinskRegion.street, "\n")] = '\0';
            printf("Введите номер дома студента:\t");
            (students + i)->address->MinskRegion.house = enterEl();
            printf("Введите номер квартиры студента:\t");
            (students + i)->address->MinskRegion.flat = enterEl();
        }
        else if ((students + i)->isLocale == 2)
        {
            printf("Введите область студента:\t");
            rewind(stdin);
            fgets((students + i)->address->outMinskRegion.region, K, stdin);
            (students + i)->address->outMinskRegion.region[strcspn((students + i)->address->outMinskRegion.region, "\n")] = '\0';
            printf("Введите район студента:\t");
            rewind(stdin);
            fgets((students + i)->address->outMinskRegion.district, K, stdin);
            (students + i)->address->outMinskRegion.district[strcspn((students + i)->address->outMinskRegion.district, "\n")] = '\0';
            printf("Введите город студента:\t");
            rewind(stdin);
            fgets((students + i)->address->outMinskRegion.city, K, stdin);
            (students + i)->address->outMinskRegion.city[strcspn((students + i)->address->outMinskRegion.city, "\n")] = '\0';
            printf("Введите улицу студента:\t");
            rewind(stdin);
            fgets((students + i)->address->outMinskRegion.street, K, stdin);
            (students + i)->address->outMinskRegion.street[strcspn((students + i)->address->outMinskRegion.street, "\n")] = '\0';
            printf("Введите номер дома студента:\t");
            (students + i)->address->outMinskRegion.house = enterEl();
            printf("Введите номер квартиры студента:\t");
            (students + i)->address->outMinskRegion.flat = enterEl();
        }
        else if ((students + i)->isLocale == 3)
        {
            printf("Введите регион студента:\t");
            rewind(stdin);
            fgets((students + i)->address->Village.region, K, stdin);
            (students + i)->address->Village.region[strcspn((students + i)->address->Village.region, "\n")] = '\0';
            printf("Введите область студента:\t");
            rewind(stdin);
            fgets((students + i)->address->Village.district, K, stdin);
            (students + i)->address->Village.district[strcspn((students + i)->address->Village.district, "\n")] = '\0';
            printf("Введите название деревни студента:\t");
            rewind(stdin);
            fgets((students + i)->address->Village.village, K, stdin);
            (students + i)->address->Village.village[strcspn((students + i)->address->Village.village, "\n")] = '\0';
            printf("Введите номер дома студента:\t");
            (students + i)->address->Village.house = enterEl();
        }
        else
        {
            printf("Данного типа студента не существует");
            continue;
        }
    }
}

void printStudentsAddress(infoStudent *students, int m, int type)
{
    int count = 1;
    const char *defPlace[] = {"Минск", "Область", "Иногородние", "Из деревни"};

    if (type == 0)
    {
        printf("\nСтуденты, проживающие в Минске\n\n");
        printf("===========================================================================================\n");
        printf("| %-3s | %-20s | %-15s | %-20s | %-5s | %-10s |\n", "N", "ФИО", "Тип адреса", "Улица", "Дом", "Квартира");
        printf("===========================================================================================\n");
        for (int i = 0; i < m; i++)
        {
            if ((students + i)->isLocale == 0 && (students + i)->address != NULL)
            {
                printf("| %-3d | %-20s | %-15s | %-20s | %-5d | %-10d |\n",
                        count++,
                        (students + i)->fio,
                        defPlace[0],
                        (students + i)->address->Minsk.street,
                        (students + i)->address->Minsk.house,
                        (students + i)->address->Minsk.flat);
            }
        }
        printf("===========================================================================================\n");
    }
    else if (type == 1)
    {
        printf("\nСтуденты, проживающие в Минской области\n\n");
        printf("============================================================================================================\n");
        printf("| %-3s | %-20s | %-15s | %-20s | %-20s | %-5s | %-10s |\n", "N", "ФИО", "Тип адреса", "Город", "Улица", "Дом", "Квартира");
        printf("============================================================================================================\n");
        for (int i = 0; i < m; i++)
        {
            if ((students + i)->isLocale == 1 && (students + i)->address != NULL)
            {
                printf("| %-3d | %-20s | %-15s | %-20s | %-20s | %-5d | %-10d |\n",
                        count++,
                        (students + i)->fio,
                        defPlace[1],
                        (students + i)->address->MinskRegion.city,
                        (students + i)->address->MinskRegion.street,
                        (students + i)->address->MinskRegion.house,
                        (students + i)->address->MinskRegion.flat);
            }
        }
        printf("============================================================================================================\n");
    }
    else if (type == 2)
    {
        printf("\nИногородние студенты\n\n");
        printf("=============================================================================================================================================\n");
        printf("| %-3s | %-20s | %-15s | %-20s | %-20s | %-20s | %-20s | %-5s | %-10s |\n",
                "N", "ФИО", "Тип адреса", "Область", "Район", "Город", "Улица", "Дом", "Квартира");
        printf("=============================================================================================================================================\n");
        for (int i = 0; i < m; i++)
        {
            if ((students + i)->isLocale == 2 && (students + i)->address != NULL)
            {
                printf("| %-3d | %-20s | %-15s | %-20s | %-20s | %-20s | %-20s | %-5d | %-10d |\n",
                        count++,
                        (students + i)->fio,
                        defPlace[2],
                        (students + i)->address->outMinskRegion.region,
                        (students + i)->address->outMinskRegion.district,
                        (students + i)->address->outMinskRegion.city,
                        (students + i)->address->outMinskRegion.street,
                        (students + i)->address->outMinskRegion.house,
                        (students + i)->address->outMinskRegion.flat);
            }
        }
        printf("=============================================================================================================================================\n");
    }
    else if (type == 3)
    {
        printf("\nСтуденты, проживающие в деревне\n\n");
        printf("============================================================================================================\n");
        printf("| %-3s | %-20s | %-15s | %-20s | %-20s | %-20s | %-10s |\n", "N", "ФИО", "Тип адреса","Область", "Район", "Деревня", "Дом");
        printf("============================================================================================================\n");
        for (int i = 0; i < m; i++)
        {
            if ((students + i)->isLocale == 3 && (students + i)->address != NULL)
            {
                printf("| %-3d | %-20s | %-15s | %-20s | %-20s | %-20s | %-10d |\n",
                        count++,
                        (students + i)->fio,
                        defPlace[3],
                        (students + i)->address->Village.region,
                        (students + i)->address->Village.district,
                        (students + i)->address->Village.village,
                        (students + i)->address->Village.house);
            }
        } 
        printf("============================================================================================================\n");
    }
}

void freeMemory(infoStudent *students, int m)
{
    for (int i = 0; i < m; i++)
    {
        if ((students + i)->fio)
            free((students + i)->fio);
        if ((students + i)->address)
        {
            // Минск
            if ((students + i)->address->Minsk.street)
                free((students + i)->address->Minsk.street);
            // Минская область
            if ((students + i)->address->MinskRegion.city)
                free((students + i)->address->MinskRegion.city);
            if ((students + i)->address->MinskRegion.street)
                free((students + i)->address->MinskRegion.street);
            // Иногородние
            if ((students + i)->address->outMinskRegion.region)
                free((students + i)->address->outMinskRegion.region);
            if ((students + i)->address->outMinskRegion.district)
                free((students + i)->address->outMinskRegion.district);
            if ((students + i)->address->outMinskRegion.city)
                free((students + i)->address->outMinskRegion.city);
            if ((students + i)->address->outMinskRegion.street)
                free((students + i)->address->outMinskRegion.street);
            // Деревня
            if ((students + i)->address->Village.region)
                free((students + i)->address->Village.region);
            if ((students + i)->address->Village.district)
                free((students + i)->address->Village.district);
            if ((students + i)->address->Village.village)
                free((students + i)->address->Village.village);
            free((students + i)->address);
        }
    }
    free(students);
}
