#include "../header.h"

ClientNode *createNode(const char *username, const char *password, int balance)
{
    ClientNode *newNode = (ClientNode *)malloc(sizeof(ClientNode));
    strcpy_s(newNode->username, K, username);
    strcpy_s(newNode->password, K, password);
    newNode->balance = balance;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtEnd(linkedList *list, const char *username, const char *password, int balance)
{
    ClientNode *newNode = createNode(username, password, balance);
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
    list->countClient++;
}

int removeClient(linkedList *list, char *username)
{
    if (list->head == NULL)
        return 0;
    ClientNode *current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
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
            list->countClient--;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void findClient(linkedList *list, char *username)
{
    int found = 0;
    ClientNode *curr = list->head;
    int position = 1;
    while (curr != NULL)
    {
        if (strcmp(curr->username, username) == 0)
        {
            // printf("\033[1;32mМашина найдена на автостоянке %d, позиция: %d.\033[0m\n", i + 1, position);
            //  if (position <= (parking + i)->countPlace)
            //     printf("\033[1;32mСтатус: [НА СТОЯНКЕ]\033[0m\n");
            // else
            //     printf("\033[1;33mСтатус: [ОЧЕРЕДЬ]\033[0m\n");
            found = 1;
            break;
        }
        curr = curr->next;
        position++;
    }
    if (!found)
        printf("Клиент не найден");
}



linkedList *copyList(linkedList *list)
{
    linkedList *newList = (linkedList *)malloc(sizeof(linkedList));
    if (!newList)
        return NULL;
    newList->head = NULL;
    newList->tail = NULL;
    newList->countClient = 0;
    ClientNode *src = list->head;
    while (src != NULL)
    {
        ClientNode *newNode = (ClientNode *)malloc(sizeof(ClientNode));
        if (!newNode)
            break;
        strcpy(newNode->username, src->username);
        strcpy(newNode->password, src->password);
        newNode->balance = src->balance;
        newNode->next = NULL;
        newNode->prev = newList->tail;
        if (newList->tail != NULL)
            newList->tail->next = newNode;
        else
            newList->head = newNode;
        newList->tail = newNode;
        newList->countClient++;
        src = src->next;
    }
    return newList;
}

void printClients(linkedList *list)
{
    linkedList *newList = copyList(list);
    printf("\033[1;34m══════════════════════════════════════════════════\033[0m\n");
    printf("\033[1;34m╔════╦══════════════╦════════════════════════════╗\033[0m\n");
    printf("\033[1;34m║ №  ║ Статус       ║ Номер автомобиля           ║\033[0m\n");
    printf("\033[1;34m╠════╬══════════════╬════════════════════════════╣\033[0m\n");
    int parkedCounter = 0, queueCounter = 0, index = 0;

    ClientNode *ptr = newList->head;
    while (ptr != NULL)
    {
        parkedCounter++;
        printf("ytgg");
        ptr = ptr->next;
        index++;
    }
    free(newList);
}

void saveUserInFile(char *username, char *password, int balance)
{
    FILE *file;
    file = fopen("users.txt", "a");
    if (file == NULL)
        printf("Не удалось открыть файл для записи.\n");
    else
        fprintf(file, "user %s %s %d\n", username, password, balance);
    fclose(file);
}
