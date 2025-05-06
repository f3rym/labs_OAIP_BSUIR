#include "header.h"

struct Tree *newNodeCreate(int value)
{
    struct Tree *root = (Tree *)malloc(sizeof(Tree));
    root->key = value;
    root->left = root->right = NULL;
    return root;
}

struct Tree *searchNode(Tree *root, int value)
{
    if (root == NULL || root->key == value)
        return root;
    else if (root->key < value)
        return searchNode(root->right, value);
    else
        return searchNode(root->left, value);
}

struct Tree *insertNode(Tree *root, int value)
{
    if (root == NULL)
        return newNodeCreate(value);
    else if (value < root->key)
        root->left = insertNode(root->left, value);
    else if (value > root->key)
        root->right = insertNode(root->right, value);
    return root;
};

struct Tree *findMin(Tree *root)
{
    if (root == NULL)
        return NULL;
    else if (root->left != NULL)
        return findMin(root->left);
    return root;
}

struct Tree *findMax(Tree *root)
{
    if(root == NULL)
        return NULL;
    else if(root->right != NULL)
        return findMax(root->right);
    return root;
} 

struct Tree *deleteNode(Tree *root, int value)
{
    if (root == NULL)
        return NULL;
    if (value > root->key)
        root->right = deleteNode(root->right, value);
    else if (value < root->key)
        root->left = deleteNode(root->left, value);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL || root->right == NULL)
        {
            Tree *temp;
            if (root->left == NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            Tree *temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}

void Order1(Tree *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        Order1(root->left);
        Order1(root->right);
    }
}

void Order2(Tree *root)
{
    if (root != NULL)
    {
        Order1(root->left);
        printf("%d ", root->key);
        Order1(root->right);
    }
}

void Order3(Tree *root)
{
    if (root != NULL)
    {
        Order1(root->left);
        Order1(root->right);

        printf("%d ", root->key);
    }
}

void printTree(Tree *root, int n)
{
    if (root == NULL)
        return;
    n += 5;
    printTree(root->right, n);
    for(int i = 0; i < n; i++)
        printf(" ");
    printf("%d\n", root->key);
    printTree(root->left, n);
}

void freeTree(Tree **root)
{
    if (root == NULL || *root == NULL)
        return;
    freeTree(&(*root)->left);
    freeTree(&(*root)->right);
    free(*root);
    *root = NULL;
}

struct Tree *manageTree(Tree *root)
{
    int m;
    while (1)
    {
        printf("\n\033[1;34m════════════════════════════════════════\033[0m\n");
        printf("\033[1;33m1\033[0m - Добавить узел\n");
        printf("\033[1;33m2\033[0m - Удалить узел\n");
        printf("\033[1;33m3\033[0m - Обход дерева\n");
        printf("\033[1;33m4\033[0m - Вывести дерево\n");
        printf("\033[1;33m5\033[0m - Отчистить\n");
        printf("\033[1;33m6\033[0m - Поиск значения\n");
        printf("\033[1;33m7\033[0m - Найти max\n");
        printf("\033[1;33m8\033[0m - Найти min\n");
        printf("\033[1;33m9\033[0m - Выход\n");
        printf("\033[1;34m──────────────────────────────────────────\033[0m\n");
        printf("\033[1;32m$ \033[0m");
        m = enterEl();
        if (m == 1)
        {
            int value;
            printf("Введите значение для добавления: ");
            value = enterEl();
            root = insertNode(root, value);
            printf("Узел добавлен.\n");
        }
        else if (m == 2)
        {
            int value;
            printf("Введите значение для удаления: ");
            value = enterEl();
            if (searchNode(root, value))
            {
                root = deleteNode(root, value);
                printf("\nУзел %d удален.\n", value);
            }
            else
                printf("\nУзел %d не найден.\n", value);
        }
        else if (m == 3)
        {
            int type;
            while (1)
            {
                printf("Введите тип обхода(1 - Прямой | 2 - Симметричный | 3 - Обратный) : ");
                type = enterEl();
                if (type < 1 || type > 3)
                {
                    printf("Данного типа обхода не существует, попробуйте снова.\n");
                }
                else
                    break;
            }
            if (type == 1)
                Order1(root);
            else if (type == 2)
                Order2(root);
            else
                Order3(root);
        }
        else if(m == 4)
        {
            printTree(root, 0);
        }
        else if(m == 5)
        {
            freeTree(&root);
            printf("\nДерево очищено.\n");
        }
        else if(m == 6)
        {
            int value;
            Tree* ans;
            printf("\nВведите значение, которое хотите найти: ");
            value = enterEl();
            ans = searchNode(root, value);
            if (ans)
                printf("\nУзел %d найден.\n", value);
            else
                printf("\nУзел %d не найден.\n", value);
        }
        else if(m == 7)
        {
            Tree *mx = findMax(root);
            if (mx)
                printf("\nМаксимальный ключ: %d\n", mx->key);
            else
                printf("\nДерево пусто.\n");
        }
        else if(m == 8)
        {
            Tree *mn = findMin(root);
            if (mn)
                printf("\nМинимальный ключ: %d\n", mn->key);
            else
                printf("\nДерево пусто.\n");
        }
        else if (m == 9)
        {
            printf("\033[1;31m\nВыход из системы. \033[0m\n");
            break;
        }
        else
        {
            printf("\033[1;31m\nОшибка. Данной команды не существует!\033[0m\n");
        }
    }
    return root;
}
