#include "header.h"

void initClientAndProductAndBucketList(linkedList *list, productList *prList, bucketList *btlist)
{
    list->head = NULL;
    list->tail = NULL;
    list->countClient = 0;
    prList->head = NULL;
    prList->tail = NULL;
    prList->countProduct = 0;
    btlist->head = NULL;
    btlist->tail = NULL;
}

void managerInfoClients(productList *list, char *user, bucketList *btList)
{
    int m;
    while (1)
    {
        printf("\033[1;34m══════════════════════════════════\033[0m\n");
        printf(" Пользователь: \033[1;32m%s\033[0m   \n", user);
        printf("\033[1;34m──────────────────────────────────\033[0m\n");
        printf("\033[1;33m1\033[0m - Посмотреть товары\n");
        printf("\033[1;33m2\033[0m - Добавить товар в корзину\n");
        printf("\033[1;33m3\033[0m - Удалить товар из корзины\n");
        printf("\033[1;33m4\033[0m - Вывести корзину\n");
        printf("\033[1;33m5\033[0m - Оформить заказ\n");
        printf("\033[1;33m6\033[0m - Проверить баланс\n");
        printf("\033[1;33m7\033[0m - Выход\n");
        printf("\033[1;34m──────────────────────────────────\033[0m\n");
        printf("\033[1;33m%s\033[1;37m$ \033[0m", user);
        m = enterEl();
        if (m == 1)
        {
            printProducts(list);
        }
        else if (m == 2)
        {
            AddItem(btList, list, user);
        }
        else if (m == 3)
        {
            //Soooooooooooooooon
        }
        else if (m == 4)
        {
            printProductsInBucket(btList, user);
        }
        else if (m == 5)
        {
            //Soooooooooooooooon
        }
        else if (m == 6)
        {
            //Soooooooooooooooon
        }
        else if(m == 7)
        {
            break;
        }
        else 
            printf("Данной команды не существует попробуй снова.\n");
    }
}

void managerInfoAdmins(linkedList *userList, productList *list, char *user, bucketList *btList)
{
    int m;
    while (1)
    {
        printf("\033[1;34m══════════════════════════════════\033[0m\n");
        printf("\033[1;33m1\033[0m - Добавить товар в магазин\n");
        printf("\033[1;33m2\033[0m - Удалить товар из магазина\n");
        printf("\033[1;33m3\033[0m - Посмотреть товары\n");
        printf("\033[1;33m4\033[0m - Управление пользователями\n");
        printf("\033[1;33m5\033[0m - Просмотр заказов\n");
        printf("\033[1;33m6\033[0m - Добавить товар в корзину\n");
        printf("\033[1;33m7\033[0m - Удалить товар из корзины\n");
        printf("\033[1;33m8\033[0m - Вывести корзину\n");
        printf("\033[1;33m9\033[0m - Выход\n");
        printf("\033[1;34m──────────────────────────────────\033[0m\n");
        printf("\033[1;33m%s\033[1;37m$ \033[0m", user);
        m = enterEl();
        if (m == 1)
        {
            int id;
            char nameProduct[K];
            int priceProduct, count;
            printf("Введите название товара: ");
            rewind(stdin);
            fgets(nameProduct, K, stdin);
            nameProduct[strcspn(nameProduct, "\n")] = '\0';
            printf("Введите количество: ");
            count = enterEl();
            printf("Введите цену: ");
            priceProduct = enterEl();
            id = insertAtEndProduct(list, nameProduct, priceProduct, count);
            saveProductInFile(id, nameProduct, priceProduct, count);
        }
        else if (m == 2)
        {
            char nameProduct[K];
            printf("Введите название товара: ");
            rewind(stdin);
            fgets(nameProduct, K, stdin);
            nameProduct[strcspn(nameProduct, "\n")] = '\0';
            if (removeProduct(list, nameProduct) == 1)
                printf("Продукт успешно удален.\n");
            else
                printf("Продукт не найден.\n");
        }
        else if (m == 3)
        {
            printProducts(list);
        }
        else if (m == 4)
        {
            // Soooooooooooooooon
        }
        else if (m == 5)
        {
            // Soooooooooooooooon
        }
        else if (m == 6)
        {
            AddItem(btList, list, user);
        }
        else if (m == 7)
        {
            // Soooooooooooooooon
        }
        else if (m == 8)
        {
            printProductsInBucket(btList, user);
        }
        else if (m == 9)
        {
            break;
        }
        else
            printf("Данной команды не существует попробуй снова.\n");
    }
}

void checkAdmin(linkedList *userList, productList *list, char *user, bucketList *btList)
{
    if(strcmp(user, "admin") == 0)
        managerInfoAdmins(userList ,list, user, btList);
    else
        managerInfoClients(list, user, btList);
}

void freeLinkedList(linkedList *list)
{
    while (list->head != NULL)
    {
        ClientNode *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}
