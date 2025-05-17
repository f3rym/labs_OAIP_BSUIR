#include "../header.h"

void saveProductInFile(int id, const char *name, int price, int count)
{
    FILE *file;
    file = fopen("product.txt", "a");
    if (file == NULL)
        printf("Не удалось открыть файл для записи.\n");
    else
        fprintf(file, "product %d %s %d %d\n", id, name, price, count);
    fclose(file);
}

int findID(productList *list, char *name)
{
    ProductNode *curr = list->head;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
            return curr->id;
        curr = curr->next;
    }
    return 0;
}

void removeProductInFile(productList *list, int ID)
{
    FILE *fin;
    FILE *fout;
    char line[K], productName[K];
    int price, count, id, newID = 1;
    fin = fopen("product.txt", "r");
    fout = fopen("product_tmp.txt", "w");
    if (fin != NULL)
    {
        while(fgets(line, K, fin))
        {
            if (sscanf(line, "product %d %s %d %d", &id, productName, &price, &count) == 4)
            {
                if(id != ID)
                {
                    fprintf(fout, "product %d %s %d %d\n", newID++, productName, price, count);
                }
            }
        }
    }
    else
        printf("Не удалось открыть файл для записи.\n");
    fclose(fin);
    fclose(fout);
    remove("product.txt");
    rename("product_tmp.txt", "product.txt");
}

ProductNode *createNodeProduct(const char *name, int price, int count)
{
    static int currentID = 1;
    int newID = currentID++;
    ProductNode *newNode = (ProductNode *)malloc(sizeof(ProductNode));
    strcpy_s(newNode->name, K, name);
    newNode->price = price;
    newNode->id = newID;
    newNode->count = count;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

int insertAtEndProduct(productList *list, const char *name, int price, int count)
{
    ProductNode *newNode = createNodeProduct(name, price, count);
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
    return newNode->id;
}

void renumberProductList(productList *list)
{
    if (!list)
        return;
    ProductNode *curr = list->head;
    int newID = 1;
    while (curr)
    {
        curr->id = newID++;
        curr = curr->next;
    }
}

int removeProduct(productList *list, const char *name)
{
    int ID;
    if (list->head == NULL)
        return 0;
    ProductNode *current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            ID = current->id;
            if (current->next != NULL)
                current->next->prev = current->prev;
            else
                list->tail = current->prev;
            if (current->prev != NULL)
                current->prev->next = current->next;
            else
                list->head = current->next;
            free(current);
            list->countProduct--;
            removeProductInFile(list, ID);
            renumberProductList(list);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int findProduct(productList *list, char *name)
{
    ProductNode *curr = list->head;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
            return 1;
        curr = curr->next;
    }
    return 0;
}


int findProductPrice(productList *list, char* name)
{
    ProductNode *curr = list->head;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
        {
            return curr->price;
        }
        curr = curr->next;
    }
    return 0;
}

void printProducts(productList *plist)
{
    ProductNode *cur = plist->head;
    printf("ID  Name                          Price  Count\n");
    while (cur)
    {
        printf("%-3d %-30s %-6d %-5d\n", cur->id, cur->name, cur->price, cur->count);
        cur = cur->next;
    }
}