#include "../header.h"

char *findClientPass(linkedList *list, char *username, char *password)
{
    ClientNode *curr = list->head;
    while (curr != NULL)
    {
        if (strcmp(curr->username, username) == 0 && strcmp(curr->password, password) == 0)
        {
            printf("\n\033[1;32mВы успешно вошли под \033[1;33m%s\033[0m\n", curr->username);
            return curr->username;
        }
        curr = curr->next;
    }
    printf("\n\033[1;31mНеверный логин или пароль, попробуйте снова.\033[0m\n");
    return NULL;
}

void loadUsersAndProductAndBucketInFile(linkedList *list, productList *prList, bucketList *btlist)
{
    // Загрузка пользователей
    FILE *file1 = fopen("users.txt", "r");
    if (file1 != NULL)
    {
        char line[K];
        while (fgets(line, sizeof(line), file1))
        {
            if (strncmp(line, "user ", 5) == 0)
            {
                char username[K], password[K];
                int balance;
                if (sscanf(line, "user %49s %49s %d", username, password, &balance) == 3)
                {
                    username[strcspn(username, "\n")] = '\0';
                    password[strcspn(password, "\n")] = '\0';
                    insertAtEnd(list, username, password, balance);
                }
            }
        }
        fclose(file1);
    }
    FILE *file2 = fopen("product.txt", "r");
    if (file2 != NULL)
    {
        char line[K];
        while (fgets(line, sizeof(line), file2))
        {
            if (strncmp(line, "product ", 8) == 0)
            {
                int id, price, count;
                char name[K];
                if (sscanf(line, "product %d %s %d %d", &id, name, &price, &count) == 4)
                {
                    name[strcspn(name, "\n")] = '\0';
                    insertAtEndProduct(prList, name, price, count);
                }
            }
        }
        fclose(file2);
    }
    printf(":) Данные из файлов успешно подгружены\n");
}
char *login(linkedList *list)
{
    while (1)
    {
        int position;
        char command[K];
        char *loginOriginal;
        loginOriginal = (char *)malloc(K * sizeof(char));
        strcpy(loginOriginal, "Гость");
        printf("\033[1;34mЗарегистрируйтесь \033[1;32m/reg \033[1;34mили войдите \033[1;32m/login \033[0m:\n");
        printf("\033[1;33m%s\033[1;37m$ \033[0m", loginOriginal);
        fgets(command, K, stdin);
        command[strcspn(command, "\n")] = '\0';
        if (strncmp(command, "/reg", 4) == 0)
        {
            char *login, *password, *passwordCheck;
            login = (char *)malloc(K * sizeof(char));
            password = (char *)malloc(K * sizeof(char));
            passwordCheck = (char *)malloc(K * sizeof(char));
            printf("\033[1;34mВведите логин.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", loginOriginal);
            fgets(login, K, stdin);
            login[strcspn(login, "\n")] = '\0';
            printf("\033[1;34mВведите пароль.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", loginOriginal);
            password = inputPassword();
            printf("\n\033[1;34mПовторите пароль.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", loginOriginal);
            passwordCheck = inputPassword();
            if (strcmp(password, passwordCheck) == 0)
            {
                list->countClient++;
                insertAtEnd(list, login, password, 100);
                saveUserInFile(login, password, 100);
                printf("\n\033[1;32m:) Вы успешно зарегистрированы.\033[0m\n");
            }
            else
                printf("\n\033[1;31m:( Пароли не совпадают...\033[0m\n");
            free(passwordCheck);
            free(password);
            free(login);
        }
        if (strncmp(command, "/login", 6) == 0)
        {
            char *login, *password;
            login = (char *)malloc(K * sizeof(char));
            password = (char *)malloc(K * sizeof(char));
            printf("\033[1;34mВведите логин.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", loginOriginal);
            fgets(login, K, stdin);
            login[strcspn(login, "\n")] = '\0';
            printf("\033[1;34mВведите пароль.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", loginOriginal);
            password = inputPassword();
            loginOriginal = findClientPass(list, login, password);
            if (loginOriginal != NULL)
                return loginOriginal;
            else
                free(loginOriginal);
        }
    }
}

char *inputPassword()
{
    char *password, ch;
    int i = 0;
    password = (char *)malloc(K * sizeof(char));
    while ((ch = _getch()) != '\n' && ch != '\r')
    {
        if (i < K)
        {
            if (ch == '\b')
            {
                i--;
                printf("\b  \b");
            }
            else
            {
                *(password + i++) = ch;
                printf("*");
            }
        }
        *(password + i) = '\0';
    }
    return password;
}
