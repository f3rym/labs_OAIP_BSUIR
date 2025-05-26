#include "header.h"

Node *createNode(char *carNumber)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy_s(newNode->carNumber, K, carNumber);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtEnd(linkedList *list, char *carNumber)
{
    Node *newNode = createNode(carNumber);
    if (list->head == NULL)
    {
        list->head = list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->countCars++;
}

int removeCar(linkedList *list, char *carNumber)
{
    if (list->head == NULL)
        return 0;
    Node *current = list->head;
    while (current == NULL)
    {
        if (strcmp(current->carNumber, carNumber) == 0)
        {
            if (current->next != NULL)
                current->next->prev = current->prev;
            else
                list->tail = current->prev;
            if (current->prev != NULL)
                current->prev->next = current->next;
            else
                list->head = current->next;
            free(current);
            list->countCars--;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void findCar(infoParking *parking, int countParkingLot, char *carNumber)
{
    int found = 0;
    for (int i = 0; i < countParkingLot; i++)
    {
        Node *curr = (parking + i)->list->head;
        int position = 1;
        while (curr != NULL)
        {
            if (strcmp(curr->carNumber, carNumber) == 0)
            {
                printf("\033[1;32mМашина найдена на автостоянке %d, позиция: %d.\033[0m\n", i + 1, position);
                if (position <= (parking + i)->countPlace)
                    printf("\033[1;32mСтатус: [НА СТОЯНКЕ]\033[0m\n");
                else
                    printf("\033[1;33mСтатус: [ОЧЕРЕДЬ]\033[0m\n");
                found = 1;
                break;
            }
            curr = curr->next;
            position++;
        }
    }
    if (!found)
        printf("\033[1;31mМашина с номером \"%s\" не найдена на автостоянках.\033[0m\n", carNumber);
}

linkedList *copyList(linkedList *list)
{
    linkedList *newList = (linkedList *)malloc(sizeof(linkedList));
    if (!newList)
        return NULL;
    newList->head = NULL;
    newList->tail = NULL;
    newList->countCars = 0;
    Node *src = list->head;
    while (src != NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (!newNode)
            break;
        strcpy(newNode->carNumber, src->carNumber);
        newNode->next = NULL;
        newNode->prev = newList->tail;
        if (newList->tail != NULL)
            newList->tail->next = newNode;
        else
            newList->head = newNode;
        newList->tail = newNode;
        newList->countCars++;
        src = src->next;
    }
    return newList;
}

void printCars(linkedList *list, int countPlace)
{
    int count = 0;
    int freePlaces;
    linkedList *newList = copyList(list);
    freePlaces = countPlace - newList->countCars;
    if (freePlaces < 0)
        freePlaces = 0;
    printf("\033[1;34m══════════════════════════════════════════════════\033[0m\n");
    printf("\033[1;36m  Список машин на автостоянке:\033[0m\n");
    printf("\033[1;32mВсего мест: %d    Свободных мест: %d\033[0m\n", countPlace, freePlaces);
    printf("\033[1;34m╔════╦══════════════╦════════════════════════════╗\033[0m\n");
    printf("\033[1;34m║ №  ║ Статус       ║ Номер автомобиля           ║\033[0m\n");
    printf("\033[1;34m╠════╬══════════════╬════════════════════════════╣\033[0m\n");
    int parkedCounter = 0, queueCounter = 0, index = 0;

    Node *ptr = newList->head;
    while (ptr != NULL)
    {
        if (index < countPlace)
        {
            parkedCounter++;
            printf("\033[1;32m║ %2d ║ %-12s ║ %-26s ║\033[0m\n", parkedCounter, "[НА СТОЯНКЕ]", ptr->carNumber);
        }
        else
        {
            queueCounter++;
            printf("\033[1;33m║ %2d ║ %-14s ║ %-26s ║\033[0m\n", queueCounter, "[ОЧЕРЕДЬ]   ", ptr->carNumber);
        }
        ptr = ptr->next;
        index++;
    }
    printf("\033[1;34m╚════╩══════════════╩════════════════════════════╝\033[0m\n");
    free(newList);
}

struct infoParking *mem(int countParkingLot)
{
    infoParking *parking;
    parking = (infoParking *)malloc(countParkingLot * sizeof(infoParking));
    if (parking == NULL)
        return NULL;
    return parking;
}

void memNew(infoParking **parking, int *countParkingLot, int mNew)
{
    infoParking *tmp = (infoParking *)realloc(*parking, (*countParkingLot + 1) * sizeof(infoParking));
    if (tmp == NULL)
        printf("\033[1;31mОшибка выделения памяти для новой автостоянки.\033[0m\n");
    else
    {
        *parking = tmp;
        (*parking + *countParkingLot)->countPlace = mNew;
        (*parking + *countParkingLot)->list = (linkedList *)malloc(sizeof(linkedList));
        if ((*parking + *countParkingLot)->list == NULL)
            printf("\033[1;31mОшибка выделения памяти для списка новой автостоянки.\033[0m\n");
        else
        {
            (*parking + *countParkingLot)->list->head = NULL;
            (*parking + *countParkingLot)->list->tail = NULL;
            (*parking + *countParkingLot)->list->countCars = 0;
            (*countParkingLot)++;
            printf("\033[1;32mНовая автостоянка успешно добавлена! Теперь их %d.\033[0m\n", *countParkingLot);
        }
    }
}

void enterInfoParking(infoParking *parking, int countParkingLot)
{
    for (int i = 0; i < countParkingLot; i++)
    {
        int m;
        printf("\033[1;32mВведите кол-во мест на автостоянке %d: \033[0m", i + 1);
        m = enterEl();
        (parking + i)->countPlace = m;
        (parking + i)->list = (linkedList *)malloc(sizeof(linkedList));
        (parking + i)->list->head = NULL;
        (parking + i)->list->tail = NULL;
        (parking + i)->list->countCars = 0;
    }
}

void managerInfoCars(infoParking **parking, int *countParkingLot)
{
    int m;
    while (1)
    {
        printf("\033[1;34m════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\033[0m\n");
        printf("\033[1;33m1\033[0m - Постановка машины   |   ");
        printf("\033[1;33m2\033[0m - Удаление машины   |   ");
        printf("\033[1;33m3\033[0m - Просмотр автомобилей   |   ");
        printf("\033[1;33m4\033[0m - Добавление автостоянки   |   ");
        printf("\033[1;33m5\033[0m - Поиск машины   |   ");
        printf("\033[1;33m6\033[0m - Выход\n");
        printf("\033[1;34m────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\033[0m\n");
        printf("\033[1;32m$ \033[0m");
        m = enterEl();

        if (m == 1)
        {
            char carNumber[K];
            int numberParking;
            while (1)
            {
                printf("\n\033[1;36mВведите номер автостоянки для парковки машины(1 - %d): \033[0m", *countParkingLot);
                numberParking = enterEl() - 1;
                if (numberParking >= 0 && numberParking < *countParkingLot)
                    break;
                else
                    printf("\033[1;31mТакой автостоянки не существует, попробуйте снова.\033[0m\n");
            }
            printf("\033[1;36mВведите номер автомобиля: \033[0m");
            rewind(stdin);
            fgets(carNumber, K, stdin);
            carNumber[strcspn(carNumber, "\n")] = '\0';
            insertAtEnd((*parking + numberParking)->list, carNumber);
            printf("\033[1;32mМашина успешно добавлена!\033[0m\n");
        }
        else if (m == 2)
        {
            char carNumber[K];
            int numberParking;
            while (1)
            {
                printf("\n\033[1;36mВведите номер автостоянки для удаления машины(1 - %d): \033[0m", *countParkingLot);
                numberParking = enterEl() - 1;
                if (numberParking >= 0 && numberParking < *countParkingLot)
                    break;
                else
                    printf("\033[1;31mТакой автостоянки не существует, попробуйте снова.\033[0m\n");
            }
            printf("\033[1;36mВведите номер автомобиля: \033[0m");
            rewind(stdin);
            fgets(carNumber, K, stdin);
            carNumber[strcspn(carNumber, "\n")] = '\0';
            if (removeCar((*parking + numberParking)->list, carNumber) == 1)
                printf("\033[1;31mМашина удалена.\033[0m\n");
            else
                printf("\033[1;31mМашина не была найдена.\033[0m\n");
        }
        else if (m == 3)
        {
            int numberParking;
            while (1)
            {
                printf("\n\033[1;36mВведите номер автостоянки для просмотра(1 - %d): \033[0m", *countParkingLot);
                numberParking = enterEl() - 1;
                if (numberParking >= 0 && numberParking < *countParkingLot)
                    break;
                else
                    printf("\033[1;31mТакой автостоянки не существует, попробуйте снова.\033[0m\n");
            }
            printf("\033[1;35m\nСписок машин на автостоянке %d:\033[0m\n", numberParking + 1);
            printCars((*parking + numberParking)->list, (*parking + numberParking)->countPlace);
        }
        else if (m == 4)
        {
            int mNew;
            printf("\033[1;33m\n[!] Добавление новой автостоянки.\033[0m\n");
            printf("\033[1;36mВведите количество мест для новой автостоянки: \033[0m");
            mNew = enterEl();
            memNew(parking, countParkingLot, mNew);
        }
        else if (m == 5)
        {
            char carNumber[K];
            printf("\033[1;36mВведите номер автомобиля для поиска: \033[0m");
            rewind(stdin);
            fgets(carNumber, K, stdin);
            carNumber[strcspn(carNumber, "\n")] = '\0';
            findCar(*parking, *countParkingLot, carNumber);
        }
        else if (m == 6)
        {
            printf("\033[1;31m\nВыход из системы. \033[0m\n");
            break;
        }
        else
        {
            printf("\033[1;31m\nОшибка. Данной команды не существует!\033[0m\n");
        }
    }
}

void freeLinkedList(linkedList *list)
{
    while (list->head != NULL)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

void memClear(infoParking *parking, int countParkingLot)
{
    for (int i = 0; i < countParkingLot; i++)
    {
        if ((parking + i)->list != NULL)
        {
            freeLinkedList((parking + i)->list);
            free((parking + i)->list);
        }
    }
    free(parking);
}
