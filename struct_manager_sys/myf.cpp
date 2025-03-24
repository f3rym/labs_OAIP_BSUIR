#include "header.h"

int CheckElement(int a, int y)
{
    if (y != 1 || a <= 0 || a >= INT_MAX)
    {
        printf("\n\033[31mОшибка. Введено не число или оно > %d. Попробуй снова.\033[0m\n\n", INT_MAX);
        rewind(stdin);
        return 0;
    }
    else
        return 1;
}

int enterEl()
{
    int el, y;
    while (1)
    {
        y = scanf_s("%d", &el);
        if (CheckElement(el, y))
            break;
    };
    return el;
}

char *inputPassword()
{
    char *password, ch;
    int i = 0;
    password = (char *)malloc(MaxStringSize * sizeof(char));
    while ((ch = _getch()) != '\n' && ch != '\r')
    {
        if (i < MaxStringSize)
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

int findUser(char **usersList, int *usersCount, char *login, char *password)
{
    for (int i = 0; i < *usersCount; i += 2)
    {
        if (strcmp(*(usersList + i), login) == 0)
        {
            if (strcmp(*(usersList + i + 1), password) == 0)
            {
                printf("\n\033[1;32mВы успешно вошли под \033[1;33m%s\033[0m\n", *(usersList + i));
                return i;
            }
            else
            {
                printf("\n\033[1;31mНеверный пароль, попробуйте снова.\033[0m\n");
                return 0;
            }
        }
    }
    printf("\n\033[1;31m:( Не нашел совпадения\033[0m\n");
    return -1;
}

void saveDbInFile(blockbase *db)
{
    FILE *file;
    file = fopen("structbase.fesql", "a");
    if (file == NULL)
        printf("Не удалось открыть файл для записи.\n");
    else
        fprintf(file, "blockbase %s\n", db->nameDb);
    fclose(file);
}

void saveTableInFile(table *def, char *columns)
{
    FILE *file;
    file = fopen("structbase.fesql", "a");
    if (file == NULL)
        printf("Не удалось открыть файл для записи.\n");
    else
        fprintf(file, "\nTABLE %s (%s)", def->nameTb, columns);
    fclose(file);
}

void saveRowInFile(table *tbEdit, char *columns, char *rowName)
{
    FILE *file;
    file = fopen("structbase.fesql", "a");
    if (file == NULL)
        printf("Не удалось открыть файл для записи.\n");
    else
        fprintf(file, "\nINSERT %s (%s) VALUES (%s)", tbEdit->nameTb, columns, rowName);
    fclose(file);
}

char **memUser(char **usersList, const char *login, const char *password, int *usersCount)
{
    if (*usersCount == 1)
    {
        usersList = (char **)malloc(sizeof(char *));
        *usersList = (char *)malloc(MaxStringSize * sizeof(char));
        strcpy(*usersList, login);
    }
    else
    {
        usersList = (char **)realloc(usersList, (*usersCount + 1) * sizeof(char *));
        *(usersList + *usersCount - 1) = (char *)malloc(MaxStringSize * sizeof(char));
        *(usersList + *usersCount) = (char *)malloc(MaxStringSize * sizeof(char));
        strcpy(*(usersList + *usersCount - 1), login);
        strcpy(*(usersList + *usersCount), password);
    }
    return usersList;
}
// Проверки на неверный ввод команды...
table *memRows(table *tbEdit, char *columns, char *rowName, int isLoad)
{
    char **columnsEnter, *token;
    int rowIndex = tbEdit->rowCount, colIndex = 0;
    // Перераспределяем память для строк таблицы (увеличиваем количество строк)
    if (rowIndex > 0)
    {
        tbEdit->valRow = (char ***)realloc(tbEdit->valRow, (rowIndex + 1) * sizeof(char **));
        if (tbEdit->valRow == NULL)
        {
            printf("Error reallocating memory for rows\n");
            return NULL;
        }
    }
    else
    {
        tbEdit->valRow = (char ***)malloc((rowIndex + 1) * sizeof(char **));
        if (tbEdit->valRow == NULL)
        {
            printf("Error reallocating memory for rows\n");
            return NULL;
        }
    }

    // Выделяем память для новой строки (только для новой строки)
    *(tbEdit->valRow + rowIndex) = (char **)malloc(tbEdit->columnsCount * sizeof(char *));
    if (*(tbEdit->valRow + rowIndex) == NULL)
    {
        printf("Error allocating memory for new row\n");
        return NULL;
    }

    // Для каждой ячейки в новой строке выделяем память
    for (int j = 0; j < tbEdit->columnsCount; j++)
    {
        *(*(tbEdit->valRow + rowIndex) + j) = (char *)malloc(MaxStringSize * sizeof(char));
        if (*(*(tbEdit->valRow + rowIndex) + j) == NULL)
        {
            printf("Error allocating memory for new cell\n");
            return NULL;
        }
    }
    if (isLoad == 0)
        saveRowInFile(tbEdit, columns, rowName);
    // Разделяем названия столбцов
    columnsEnter = (char **)malloc(DefMaxColumns * sizeof(char *));
    for (int i = 0; i < DefMaxColumns; i++)
        *(columnsEnter + i) = (char *)malloc(MaxStringSize * sizeof(char));
    token = strtok(columns, ", ");
    while (token && colIndex < DefMaxColumns)
    {
        strncpy(*(columnsEnter + colIndex), token, MaxStringSize - 1);
        *(*(columnsEnter + colIndex) + MaxStringSize - 1) = '\0';
        colIndex++;
        token = strtok(NULL, ", ");
    }
    // Разделяем данные строки и присваиваем их ячейкам
    token = strtok(rowName, ", ");
    colIndex = 0;
    while (token && colIndex < tbEdit->columnsCount)
    {
        strncpy(*(*(tbEdit->valRow + rowIndex) + colIndex), token, MaxStringSize - 1);
        *(*(*(tbEdit->valRow + rowIndex) + colIndex) + MaxStringSize - 1) = '\0';
        colIndex++;
        token = strtok(NULL, ", ");
    }
    // Увеличиваем количество строк в таблице
    tbEdit->rowCount++;
    if (isLoad == 0)
        printf("\033[1;32m:) Данные успешно занесены.\033[0m\n");
    // Освобождаем память для columnsEnter
    for (int i = 0; i < DefMaxColumns; i++)
        free(*(columnsEnter + i));
    free(columnsEnter);
    return tbEdit;
}

table *mem(char *tableName, char *columns, int isLoad)
{
    char *token, **columnsName, *columnsDef;
    table *def;
    def = (table *)malloc(sizeof(table));
    def->nameTb = (char *)malloc((strlen(tableName) + 1) * sizeof(char));
    columnsDef = (char *)malloc(MaxStringSize * 5 * sizeof(char));
    strcpy(columnsDef, columns);
    strcpy(def->nameTb, tableName);
    def->columnsCount = 0;
    def->maxRow = DefMaxRow;
    def->rowCount = 0;
    // Разделение названий колонн из команды
    columnsName = (char **)malloc(DefMaxColumns * sizeof(char *));
    for (int i = 0; i < DefMaxColumns; i++)
        *(columnsName + i) = (char *)malloc(MaxStringSize * sizeof(char));
    token = strtok(columns, ", ");
    while (token && def->columnsCount < DefMaxColumns)
    {
        strncpy(*(columnsName + def->columnsCount), token, MaxStringSize - 1);
        *(*(columnsName + def->columnsCount) + MaxStringSize - 1) = '\0';
        def->columnsCount++;
        token = strtok(NULL, ", ");
    }
    // Выделение памяти для столбцов
    def->valColumns = (char **)malloc(def->columnsCount * sizeof(char *));
    for (int i = 0; i < def->columnsCount; i++)
    {
        *(def->valColumns + i) = (char *)malloc(MaxStringSize * sizeof(char));
        strcpy(*(def->valColumns + i), *(columnsName + i));
    }
    if (isLoad == 0)
    {
        saveTableInFile(def, columnsDef);
        printf("\033[1;32mУспешно создана таблица \033[1;34m%s\033[0m со столбцами:\n", def->nameTb);
        for (int i = 0; i < def->columnsCount; i++)
            printf("%s\n", *(def->valColumns + i));
    }
    // Освобождаем память
    for (int i = 0; i < def->columnsCount; i++)
        free(*(columnsName + i));
    free(columnsDef);
    free(columnsName);
    return def;
}

blockbase *createDB(char *blockbaseName, int isLoaded)
{
    blockbase *initDb = (blockbase *)malloc(sizeof(blockbase));
    if (!initDb)
        return NULL;
    initDb->tableCount = 0;
    initDb->nameDb = (char *)malloc(MaxStringSize * sizeof(char));
    strcpy(initDb->nameDb, blockbaseName);
    if (isLoaded == 0)
    {
        saveDbInFile(initDb);
        printf("\033[1;32mУспешно создана база данных \033[1;34m%s\033[0m\n", initDb->nameDb);
    }
    return initDb;
}

blockbase *loadDbInFile(blockbase *db)
{
    int isLoad = 1;
    FILE *file;
    file = fopen("structbase.fesql", "r");
    if (file != NULL)
    {
        char *line;
        line = (char *)malloc(MaxStringSize * sizeof(char));
        while (fgets(line, MaxStringSize, file))
        {
            if (strncmp(line, "blockbase", 8) == 0 && db == NULL)
            {
                char *blockbaseName;
                blockbaseName = (char *)malloc(MaxStringSize * sizeof(char));
                sscanf(line, "blockbase %s", blockbaseName);
                blockbaseName[strcspn(blockbaseName, "\n")] = '\0';
                db = createDB(blockbaseName, isLoad);
                free(blockbaseName);
            }
            else if (strncmp(line, "TABLE", 5) == 0)
            {
                char *tableName, *columns;
                tableName = (char *)malloc(MaxStringSize * sizeof(char));
                columns = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
                int y = sscanf(line, "TABLE %s (%[^)])", tableName, columns);
                if (y == 2)
                {
                    *(db->tables + db->tableCount) = mem(tableName, columns, isLoad);
                    db->tableCount++;
                }
                free(tableName);
                free(columns);
            }
            else if (strncmp(line, "INSERT", 6) == 0)
            {
                int tablesFound = 0;
                char *tableName, *columns, *rowValue;
                tableName = (char *)malloc(MaxStringSize * sizeof(char));
                columns = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
                rowValue = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
                sscanf(line, "INSERT %s (%[^)]) VALUES (%[^)])", tableName, columns, rowValue);
                for (int i = 0; i < db->tableCount; i++)
                {
                    if (strcmp(db->tables[i]->nameTb, tableName) == 0)
                    {
                        db->tables[i] = memRows(db->tables[i], columns, rowValue, isLoad);
                        tablesFound = 1;
                        break;
                    }
                }
                if (!tablesFound)
                    printf("\033[1;31m:( Данной таблицы не существует.\033[0m\n");
                free(tableName);
                free(columns);
                free(rowValue);
            }
        }
        fclose(file);
        free(line);
        printf(":) Данные загружены\n");
    }
    return db;
}

void ls(blockbase *db)
{
    if (db != NULL)
    {
        printf("\033[1;36m============================================================\033[0m\n");
        printf("\033[1;32mСписок созданных структур данных: \033[1;34m%s\033[0m\n", db->nameDb);
        printf("\033[1;36m============================================================\033[0m\n");

        for (int i = 0; i < db->tableCount; i++)
        {
            printf("  - \033[1;32m%s\033[0m (", db->tables[i]->nameTb);
            for (int j = 0; j < db->tables[i]->columnsCount; j++)
            {
                if (j < db->tables[i]->columnsCount - 1)
                    printf(" %s, ", *(db->tables[i]->valColumns + j));
                else
                    printf("%s", *(db->tables[i]->valColumns + j));
            }
            printf(" )\n");
        }
    }
    else
        printf("\033[1;31m:( Доступных баз данных нет.\033[0m\n");

    printf("\033[1;36m============================================================\033[0m\n");
}

void enterStruct(blockbase *db)
{
    /*while (1)
    {
        printf("\nВведите количество полей базы:\t");
        int y = scanf_s("%d", &def->columnsCount);
        if (CheckElement(def->columnsCount, y))
            break;
    }
    while (1)
    {
        printf("\nВведите количество строк базы:\t");
        int y = scanf_s("%d", &def->rowCount);
        if (CheckElement(def->rowCount, y))
            break;
    }*/
    printf("\nВведите названия полей:\n");
    for (int i = 0; i < db->tables[0]->columnsCount; i++)
    {
        printf("%d Поле:\t", i + 1);
        rewind(stdin);
        fgets(*(db->tables[0]->valColumns + i), MaxStringSize, stdin);
        *(*(db->tables[0]->valColumns + i) + strcspn(*(db->tables[0]->valColumns + i), "\n")) = '\0';
    }
    printf("\nВвод строк базы:\n");
    for (int i = 0; i < db->tables[0]->rowCount; i++)
        for (int j = 0; j < db->tables[0]->columnsCount; j++)
        {
            printf("%d Строка, Поле %s:", i + 1, *(db->tables[0]->valColumns + j));
            rewind(stdin);
            fgets(*(*(db->tables[0]->valRow + i) + j), MaxStringSize, stdin);
            *(*(*(db->tables[0]->valRow + i) + j) + strcspn(*(*(db->tables[0]->valRow + i) + j), "\n")) = '\0';
        }
}

void printStruct(blockbase *db, int position)
{
    printf("\033[1;36m=====================================================================\033[0m\n");
    printf("\033[1;32m  Таблица: \033[1;34m%s\033[0m\n", db->tables[position]->nameTb);
    printf("\033[1;36m=====================================================================\033[0m\n");
    printf("|");
    for (int i = 0; i < db->tables[position]->columnsCount; i++)
        printf(" %-15s |", *(db->tables[position]->valColumns + i));
    printf("\n");
    printf("\033[1;36m|");
    for (int i = 0; i < db->tables[position]->columnsCount; i++)
        printf("-----------------|");
    printf("\033[0m\n");

    if (db->tables[position]->rowCount > 0)
    {
        for (int i = 0; i < db->tables[position]->rowCount; i++)
        {
            printf("|");
            for (int j = 0; j < db->tables[position]->columnsCount; j++)
                if (*(*(db->tables[position]->valRow + i) + j) != NULL && strlen(*(*(db->tables[position]->valRow + i) + j)) > 0)
                {
                    printf(" %-15s |", *(*(db->tables[position]->valRow + i) + j));
                }
                else
                {
                    printf(" %-15s |", "-");
                }
            printf("\n");
        }
    }
    printf("\033[1;36m=====================================================================\033[0m\n");
}

void blockbaseControl(blockbase *db, char *user)
{
    while (1)
    {
        int y;
        char command[MaxStringSize];
        printf("\033[1;33m%s(\033[1;36m%s\033[1;33m)\033[1;37m$ \033[0m", user, db->nameDb);
        fgets(command, MaxStringSize, stdin);
        command[strcspn(command, "\n")] = '\0';
        if (strcmp(command, "/help") == 0)
        {
            printf("\033[1;34mСписок возможных команд:\033[0m\n");
            printf("\033[1;32m1. CREATE TABLE \033[1;35mname (nameColumns)\033[0m\n");
            printf("   \033[1;33m- Описание:\033[0m Создает новую таблицу с заданным именем и колонками, которые перечисляются через запятую.\n");
            printf("   \033[1;33m- Пример:\033[0m CREATE TABLE myTable (name1, name2, name3)\n");
            printf("\033[1;32m2. SELECT * FROM \033[1;35mname\033[0m\n");
            printf("   \033[1;33m- Описание:\033[0m Печатает данные из таблицы с указанным именем.\n");
            printf("   \033[1;33m- Пример:\033[0m SELECT * FROM myTable\n");
            printf("\033[1;32m3. exit\033[0m\n");
            printf("   \033[1;33m- Описание:\033[0m Закрытие базы данных, возврат на главное меню.\n");
        }
        else if (strncmp(command, "SELECT * FROM", 13) == 0)
        {
            int tableFound = 0;
            char *tableName1;
            tableName1 = (char *)malloc(MaxStringSize * sizeof(char));
            sscanf(command, "SELECT * FROM %s", tableName1);
            tableName1[strcspn(tableName1, "\n")] = '\0';
            // Ищем из существующих таблиц нужную
            for (int i = 0; i < db->tableCount; i++)
            {
                if (strcmp(db->tables[i]->nameTb, tableName1) == 0)
                {
                    printStruct(db, i);
                    tableFound = 1;
                    break;
                }
            }
            if (!tableFound)
            {
                printf("\033[1;31m:( Данной таблицы не существует.\033[0m\n");
            }
            free(tableName1);
        }
        else if (strncmp(command, "ls", 2) == 0)
            ls(db);
        else if (strncmp(command, "INSERT INTO", 11) == 0)
        {
            int tablesFound = 0, isLoad = 0;
            char *tableName, *columns, *rowValue;
            tableName = (char *)malloc(MaxStringSize * sizeof(char));
            columns = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
            rowValue = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
            sscanf_s(command, "INSERT INTO %s (%[^)]) VALUES (%[^)])", tableName, MaxStringSize, columns, MaxStringSize * DefMaxColumns, rowValue, MaxStringSize * DefMaxColumns);
            for (int i = 0; i < db->tableCount; i++)
            {
                if (strcmp(db->tables[i]->nameTb, tableName) == 0)
                {
                    db->tables[i] = memRows(db->tables[i], columns, rowValue, isLoad);
                    tablesFound = 1;
                    break;
                }
            }
            if (!tablesFound)
                printf("\033[1;31m:( Данной таблицы не существует.\033[0m\n");
            free(tableName);
            free(columns);
            free(rowValue);
        }
        else if (strncmp(command, "CREATE TABLE", 12) == 0)
        {
            int isLoad = 0;
            char *tableName, *columns;
            tableName = (char *)malloc(MaxStringSize * sizeof(char));
            columns = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
            y = sscanf(command, "CREATE TABLE %s (%[^)])", tableName, columns);
            if (y == 2)
            {
                *(db->tables + db->tableCount) = mem(tableName, columns, isLoad);
                db->tableCount++;
            }
            //        else
            //            printf("\033[1;31mКоманда введена неверно, попробуйте \033[1;32m/help\033[0m\n");
            free(tableName);
            free(columns);
        }
        else if (strcmp(command, "exit") == 0)
            break;
        else
            printf("\033[1;31mКоманда введена неверно, попробуйте \033[1;32m/help\033[0m\n");
    }
}

char *login(char **usersList)
{
    int *usersCount;
    usersCount = (int *)malloc(sizeof(int));
    while (1)
    {
        int position;
        char command[MaxStringSize];
        if (usersList == NULL)
        {
            *usersCount = 1;
            usersList = memUser(usersList, "Гость", NULL, usersCount);
        }
        printf("\033[1;34mЗарегистрируйтесь \033[1;32m/reg \033[1;34mили войдите \033[1;32m/login \033[0m:\n");
        printf("\033[1;33m%s\033[1;37m$ \033[0m", *usersList);
        fgets(command, MaxStringSize, stdin);
        command[strcspn(command, "\n")] = '\0';
        if (strncmp(command, "/reg", 4) == 0)
        {
            char *login, *password, *passwordCheck;
            login = (char *)malloc(MaxStringSize * sizeof(char));
            password = (char *)malloc(MaxStringSize * sizeof(char));
            passwordCheck = (char *)malloc(MaxStringSize * sizeof(char));
            printf("\033[1;34mВведите логин.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", *usersList);
            fgets(login, MaxStringSize, stdin);
            login[strcspn(login, "\n")] = '\0';
            printf("\033[1;34mВведите пароль.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", *usersList);
            password = inputPassword();
            printf("\n\033[1;34mПовторите пароль.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", *usersList);
            passwordCheck = inputPassword();
            if (strcmp(password, passwordCheck) == 0)
            {
                *usersCount += 2;
                usersList = memUser(usersList, login, password, usersCount);
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
            login = (char *)malloc(MaxStringSize * sizeof(char));
            password = (char *)malloc(MaxStringSize * sizeof(char));
            printf("\033[1;34mВведите логин.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", *usersList);
            fgets(login, MaxStringSize, stdin);
            login[strcspn(login, "\n")] = '\0';
            printf("\033[1;34mВведите пароль.\033[0m\n");
            printf("\033[1;33m%s\033[1;37m$ \033[0m", *usersList);
            password = inputPassword();
            position = findUser(usersList, usersCount, login, password);
            if (position != -1 && position != 0)
                return *(usersList + position);
        }
    }
}

void start(blockbase *db, char *user)
{
    while (1)
    {
        char command[MaxStringSize];
        printf("\033[1;33m%s\033[1;37m$ \033[0m", user);
        fgets(command, MaxStringSize, stdin);
        command[strcspn(command, "\n")] = '\0';
        if (strncmp(command, "CREATE blockbase", 15) == 0)
        {
            int isLoad = 0;
            char *blockbaseName;
            blockbaseName = (char *)malloc(MaxStringSize * sizeof(char));
            sscanf(command, "CREATE blockbase %s", blockbaseName);
            blockbaseName[strcspn(blockbaseName, "\n")] = '\0';
            db = createDB(blockbaseName, isLoad);
            free(blockbaseName);
        }
        else if (strncmp(command, "cd", 2) == 0)
        {
            char *blockbaseName1;
            blockbaseName1 = (char *)malloc(MaxStringSize * sizeof(char));
            int y = sscanf(command, "cd %s", blockbaseName1);
            if (y == 1)
            {
                blockbaseName1[strcspn(blockbaseName1, "\n")] = '\0';
                if (db != NULL)
                {
                    if (strcmp(db->nameDb, blockbaseName1) == 0)
                        blockbaseControl(db, user);
                    else
                        printf("\033[1;31m:( Данной базы данных не существует.\033[0m\n");
                }
                else
                    printf("\033[1;31m:( Данной базы данных не существует.\033[0m\n");
            }
            else
                printf("\033[1;31m:( Нет созданных баз данных.\033[0m\n");
            free(blockbaseName1);
        }
        // Разработать менеджер для структур данных
        else if (strncmp(command, "ls", 2) == 0)
            ls(db);
        else if (strcmp(command, "/help") == 0)
        {
            printf("\033[1;34mСписок возможных команд:\033[0m\n");
            printf("\033[1;32m1. CREATE blockbase \033[1;35mname\033[0m\n");
            printf("   \033[1;33m- Описание:\033[0m Создает новую базу данных с заданным именем.\n");
            printf("\033[1;32m2. cd \033[1;35mname\033[0m\n");
            printf("   \033[1;33m- Описание:\033[0m Вход в базу данных с заданным именем.\n");
            printf("\033[1;32m3. exit\033[0m\n");
            printf("   \033[1;33m- Описание:\033[0m Завершаем работу feSQL.\n");
        }
        else if (strcmp(command, "exit") == 0)
            break;
        else
            printf("\033[1;31mКоманда введена неверно, попробуйте \033[1;32m/help\033[0m\n");
    }
}

int againProg()
{
    int y, again;
    printf("\nХотите попробовать снова? \033[32mДа - 1\033[0m. \033[31mНет - 0 \033[0m:\t");
    while (1)
    {
        y = scanf_s("%d", &again);
        if (y != 1 || (again != 0 && again != 1))
        {
            printf("\033[31mОшибка. Переход к завершению...\033[0m");
            rewind(stdin);
            again = 0;
            return again;
        }
        else
            break;
    }
    return again;
}