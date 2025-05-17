#include "../header.h"



void saveBucketInFile(const char *name, char *username, int price, int count)
{
    FILE *file;
    file = fopen("bucket.txt", "a");
    if (file == NULL)
        printf("Не удалось открыть файл для записи.\n");
    else
        fprintf(file, "item %s %s %d %d\n", username, name, price, count);
    fclose(file);
}

BucketItem *createItemBucket(const char *productName, int price, int count)
{
    static int currentID = 1;
    int newID = currentID++;
    BucketItem *newNode = (BucketItem *)malloc(sizeof(BucketItem));
    strcpy_s(newNode->productName, K, productName);
    newNode->price = price;
    newNode->id = newID;
    newNode->count = count;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

BucketNode *createNodeBucket(char *username)
{
    BucketNode *newNode = (BucketNode *)malloc(sizeof(BucketNode));
    strcpy_s(newNode->username, K, username);
    newNode->sum = 0;
    newNode->countProduct = 0;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtEndBucket(BucketNode *list, const char *productName, int price, int count)
{
    BucketItem *newNode = createItemBucket(productName, price, count);
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
    list->countProduct++;
    list->sum += price * count;
}

void insertAtEndBucketNode(bucketList *list, char *username, const char *productName, int price, int count)
{
    BucketNode *newNode = createNodeBucket(username);
    insertAtEndBucket(newNode, productName, price, count);
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
}

int removeProduct(bucketList *list, const char *productName, char *username)
{
    if (list->head == NULL)
        return 0;
    BucketNode *current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
        {
            while (current->head != NULL)
            {
                if (strcmp(current->head->productName, productName) == 0)
                {
                    if (current->head->next != NULL)
                        current->head->next->prev = current->head->prev;
                    else
                        list->head->tail = current->head->prev;
                    if (current->head->prev != NULL)
                        current->head->prev->next = current->head->next;
                    else
                        list->head->head = current->head->next;
                    free(current);
                    list->head->countProduct--;
                    return 1;
                }
                current->head = current->head->next;
            }
        }
        current = current->next;
    }
    return 0;
}

void findProductInBucket(productList *list, char *name)
{
    int found = 0;
    ProductNode *curr = list->head;
    int position = 1;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
        {
            printf("\033[1;32mПользователь найден\n");
            found = 1;
            break;
        }
        curr = curr->next;
        position++;
    }
    if (!found)
        printf("Клиент не найден");
}

void printProductsInBucket(bucketList *btlist, char* username)
{
    if (btlist == NULL && btlist->head == NULL)
    {
        printf("Ваша корзина пуста.");
        return;
    }
    BucketNode *cur = btlist->head;
    printf("ID  Name                          Price  Count\n");
    while (cur)
    {
        if (strcmp(cur->username, username) == 0)
        {
            BucketItem *it = cur->head;
            while (it)
            {
                printf("%-3d %-30s %-6d %-6d\n", it->id, it->productName, it->price, it->count);
                it = it->next;
            }
            printf("SUM %d\n", cur->sum);
        }
        cur = cur->next;
    }
}

int checkCount(productList *list, int count, char* nameProduct)
{
    ProductNode *curr = list->head;
    while(curr != NULL)
    {
        if(strcmp(curr->name, nameProduct) == 0)
        {
            if(curr->count >= count)
            {
                return 1;
            }
            else 
                return 0;
        }
        curr = curr->next;
    }
    return 0;
}

void AddItem(bucketList *btList, productList *prList, char *username)
{
    char nameProduct[K];
    int count, price;
    printf("Введите название товара: ");
    rewind(stdin);
    fgets(nameProduct, K, stdin);
    nameProduct[strcspn(nameProduct, "\n")] = '\0';
    if(findProduct(prList, nameProduct) == 1)
    {
        printf("Товар найден. Введите количество: ");
        count = enterEl();
        if (checkCount(prList, count, nameProduct) == 1)
        {
            price = findProductPrice(prList, nameProduct);
            insertAtEndBucketNode(btList, username, nameProduct, price, count);
            saveBucketInFile(nameProduct, username,  price, count);
            printf("Товар добавлен в корзину!!!\n");
        }
        else
            printf("На складе %s меньше чем %d, попробуйте ввести меньшее количество.\n", nameProduct, count);
    }
    else 
        printf("Данный товар не найден");
}

// void RemoveItem()