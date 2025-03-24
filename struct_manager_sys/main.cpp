#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1;
    blockbase *db = NULL;
    char **usersList = NULL, user[MaxStringSize];
    while (again)
    {
        printf("\033[1;36mДобро пожаловать в feBlockDataManager!\033[0m\n");
        strcpy(user, login(usersList));
        db = loadDbInFile(db);
        printf("\033[1;32mВведите команду или введите /help\033[0m :\n");
        start(db, user);
        again = againProg();
    }
}