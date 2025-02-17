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

table *mem(char *tableName, char *columns)
{
    char *token, **columnsName;
    table *def;
    def = (table *)malloc(sizeof(table));
    def->nameTb = (char *)malloc(strlen(tableName) + 1);
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
    printf("\033[1;32mУспешно создана таблица \033[1;34m%s\033[0m со столбцами:\n", def->nameTb);
    for (int i = 0; i < def->columnsCount; i++)
        printf("%s\n", *(def->valColumns + i));
    // Освобождаем память
    for (int i = 0; i < def->columnsCount; i++)
        free(*(columnsName + i));
    free(columnsName);
    return def;
}
//Проверки на неверный ввод команды...
table *memRows(table *tbEdit, char *columns, char *rowName)
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
    printf("\033[1;32m:) Данные успешно занесены.\033[0m\n");
    // Освобождаем память для columnsEnter
    for (int i = 0; i < DefMaxColumns; i++)
        free(*(columnsEnter + i));
    free(columnsEnter);
    return tbEdit;
}

database *createDB(char *databaseName)
{
    database *initDb = (database *)malloc(sizeof(database));
    if (!initDb)
        return NULL;
    initDb->tableCount = 0;
    initDb->nameDb = (char *)malloc(MaxStringSize * sizeof(char));
    initDb->nameDb = databaseName;
    printf("\033[1;32mУспешно создана база данных \033[1;34m%s\033[0m\n", initDb->nameDb);
    
    return initDb;
}

void ls(database *db, int dbCheck)
{
    printf("\033[1;36m============================================================\033[0m\n");
    printf("\033[1;32mСписок созданных структур данных:\033[0m\n");
    printf("\033[1;36m============================================================\033[0m\n");

    if (dbCheck == 1)
    {
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
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Сделать обращение на выбранную таблицу а не на все db
void enterStruct(database *db)
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

void printStruct(database *db, int position)
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

void databaseControl(database *db)
{
    while (1)
    {
        int y;
        char command[MaxStringSize];
        printf("\033[1;33mГость(\033[1;36m%s\033[1;33m)\033[1;37m$ \033[0m", db->nameDb);
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
            ls(db, 1);
        else if (strncmp(command, "INSERT INTO", 11) == 0)
        {
            int tablesFound = 0;
            char *tableName, *columns, *rowValue;
            tableName = (char *)malloc(MaxStringSize * sizeof(char));
            columns = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
            rowValue = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
            sscanf(command, "INSERT INTO %s (%[^)]) VALUES (%[^)])", tableName, columns, rowValue);
            for (int i = 0; i < db->tableCount; i++)
            {
                if (strcmp(db->tables[i]->nameTb, tableName) == 0)
                {
                    db->tables[i] = memRows(db->tables[i], columns, rowValue);
                    tablesFound = 1;
                    break;
                }
                if (!tablesFound)
                    printf("\033[1;31m:( Данной таблицы не существует.\033[0m\n");
                else
                    printf("\033[1;31mКоманда введена неверно, попробуйте \033[1;32m/help\033[0m\n");
                free(tableName);
                free(columns);
                free(rowValue);
            }
        }
        else if (strncmp(command, "CREATE TABLE", 12) == 0)
        {
            char *tableName, *columns;
            tableName = (char *)malloc(MaxStringSize * sizeof(char));
            columns = (char *)malloc(MaxStringSize * DefMaxColumns * sizeof(char));
            y = sscanf(command, "CREATE TABLE %s (%[^)])", tableName, columns);
            if (y == 2)
            {
                *(db->tables + db->tableCount) = mem(tableName, columns);
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

void start(database *db)
{
    int dbCheck = 0;
    while (1)
    {
        char command[MaxStringSize];
        printf("\033[1;33mГость\033[1;37m$ \033[0m");
        fgets(command, MaxStringSize, stdin);
        command[strcspn(command, "\n")] = '\0';
        if (strncmp(command, "CREATE DATABASE", 15) == 0)
        {
            char *databaseName;
            databaseName = (char *)malloc(MaxStringSize * sizeof(char));
            sscanf(command, "CREATE DATABASE %s", databaseName);
            databaseName[strcspn(databaseName, "\n")] = '\0';
            db = createDB(databaseName);
            dbCheck = 1;
            free(databaseName);
        }
        else if (strncmp(command, "cd", 2) == 0)
        {
            char *databaseName1;
            databaseName1 = (char *)malloc(MaxStringSize * sizeof(char));
            int y = sscanf(command, "cd %s", databaseName1);
            if (y == 1)
            {
                databaseName1[strcspn(databaseName1, "\n")] = '\0';
                if (strcmp(db->nameDb, databaseName1) == 0)
                    databaseControl(db);
                else
                    printf("\033[1;31m:( Данной базы данных не существует.\033[0m\n");
            }
            else
                printf("\033[1;31m:( Данной базы данных не существует.\033[0m\n");
            free(databaseName1);
        }
        // Разработать менеджер для структур данных
        else if (strncmp(command, "ls", 2) == 0)
            ls(db, dbCheck);
        else if (strcmp(command, "/help") == 0)
        {
            printf("\033[1;34mСписок возможных команд:\033[0m\n");
            printf("\033[1;32m1. CREATE DATABASE \033[1;35mname\033[0m\n");
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
// trie
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