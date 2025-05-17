#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

#define K 100

struct ClientNode
{
    char username[K];
    char password[K];
    int balance;
    struct ClientNode *next;
    struct ClientNode *prev;
};


struct linkedList
{
    ClientNode* head;
    ClientNode* tail;
    int countClient;
};

struct ProductNode
{
    int id;
    char name[K];
    int price;
    int count;
    struct ProductNode *next;
    struct ProductNode *prev;
};

struct productList
{
    ProductNode *head;
    ProductNode *tail;
    int countProduct;
};

struct BucketItem
{
    int id;
    char productName[K];
    int price;
    int count;
    struct BucketItem *next;
    struct BucketItem *prev;
};

struct BucketNode
{
    char username[K];
    int countProduct;
    int sum;
    BucketItem *head;
    BucketItem *tail;
    struct BucketNode *next;
    struct BucketNode *prev;
};

struct bucketList
{
    BucketNode *head;
    BucketNode *tail;
};

int findProduct(productList *list, char *name);

char *inputPassword();

void saveUserInFile(char *username, char *password, int balance);

void insertAtEnd(linkedList *list, const char *username, const char *password, int balance);

int removeProduct(productList *list, const char *name);

int insertAtEndProduct(productList *list, const char *name, int price, int count);

int findID(productList *list, char *name);

void saveUserInFile(char *username, char *password, int balance);

void printProducts(productList *plist);

void saveProductInFile(int id, const char *name, int price, int count);

void printProductsInBucket(bucketList *btlist, char *username);

int enterEl();

void managerInfoClients(productList *list, char *user, bucketList *btList);

void loadUsersAndProductAndBucketInFile(linkedList *list, productList *prList, bucketList *btlist);

int findProductPrice(productList *list, char *name);

char *login(linkedList *list);

void checkAdmin(linkedList *userList, productList *list, char *user, bucketList *btList);

void AddItem(bucketList *btList, productList *prList, char *username);

void managerInfoAdmins(linkedList *userList, productList *list, char *user, bucketList *btList);

void initClientAndProductAndBucketList(linkedList *list, productList *prList, bucketList *btlist);

int againProg();

// gcc main.cpp myf.cpp source/authorze.cpp source/bucket.cpp source/products.cpp source/users.cpp mylib.cpp -o main