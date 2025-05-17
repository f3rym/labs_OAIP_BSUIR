#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1;
    linkedList *list = NULL;
    productList *prList = NULL;
    bucketList *btList = NULL;
    list = (linkedList *)malloc(sizeof(linkedList));
    prList = (productList*)malloc(sizeof(productList));
    btList = (bucketList*)malloc(sizeof(bucketList));
    char user[K];
    while (again)
    {
        initClientAndProductAndBucketList(list, prList, btList);
        printf("\033[1;36mДобро пожаловать в Интернет-магазин!\033[0m\n");
        loadUsersAndProductAndBucketInFile(list, prList, btList);
        strcpy(user, login(list));
        checkAdmin(list, prList, user, btList); 
        again = againProg();
    }
}
