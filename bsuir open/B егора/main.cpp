#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_N 1100
#define MAX_LINE 256

struct Var
{
    char name[20];
    int allocIndex;
};

void extractNameAlloc(const char *line, char *name)
{
    const char *p = line + 4;
    int j = 0;
    while (*p && !isspace((unsigned char)*p) && *p != '=' && j < 19)
    {
        name[j++] = *p;
        p++;
    }
    name[j] = '\0';
}
void extractNameDrop(const char *line, char *name)
{
    const char *p;
    int j = 0;
    p = strchr(line, '(');
    if (!p)
    {
        name[0] = '\0';
        return;
    }
    p++;
    while (*p && *p != ')' && j < 19)
    {
        name[j++] = *p;
        p++;
    }
    name[j] = '\0';
}
void printIndent(int level)
{
    int i;
    for (i = 0; i < level * 2; i++)
    {
        putchar(' ');
    }
}
int main(void)
{
    int n, i, j, L, k;
    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Ошибка чтения числа строк\n");
        return 1;
    }
    if (n < 2 || n > 1000)
    {
        fprintf(stderr, "Число строк должно быть в диапазоне [2, 1000]\n");
        return 1;
    }
    getchar();
    char *lines[MAX_N];
    for (i = 0; i < n; i++)
    {
        lines[i] = (char *)malloc(MAX_LINE);
        if (!lines[i])
        {
            fprintf(stderr, "Ошибка выделения памяти\n");
            return 1;
        }
        if (!fgets(lines[i], MAX_LINE, stdin))
        {
            fprintf(stderr, "Ошибка чтения строки %d\n", i + 1);
            return 1;
        }
        j = (int)strlen(lines[i]);
        if (j > 0 && lines[i][j - 1] == '\n')
            lines[i][j - 1] = '\0';
    }
    int match[MAX_N];
    for (i = 0; i < n; i++)
        match[i] = -1;
    Var vars[MAX_N];
    int varCount = 0;
    for (i = 0; i < n; i++)
    {
        const char *p = lines[i];
        while (*p && isspace((unsigned char)*p))
            p++;
        if (strncmp(p, "let ", 4) == 0)
        {
            char name[20];
            extractNameAlloc(p, name);
            strcpy(vars[varCount].name, name);
            vars[varCount].allocIndex = i;
            varCount++;
        }
        else if (strncmp(p, "drop(", 5) == 0)
        {
            char name[20];
            extractNameDrop(p, name);
            for (j = 0; j < varCount; j++)
            {
                if (strcmp(vars[j].name, name) == 0)
                {
                    match[vars[j].allocIndex] = i;
                    break;
                }
            }
        }
    }
    int used[MAX_N] = {0};
    for (i = 0; i < n; i++)
    {
        if (used[i])
            continue;
        {
            const char *p = lines[i];
            while (*p && isspace((unsigned char)*p))
                p++;
            if (strncmp(p, "let ", 4) == 0)
            {
                int best = 0;
                for (L = 1; i + 2 * L - 1 < n; L++)
                {
                    int valid = 1;
                    for (k = 0; k < L; k++)
                    {
                        const char *sLet = lines[i + k];
                        while (*sLet && isspace((unsigned char)*sLet))
                            sLet++;
                        if (strncmp(sLet, "let ", 4) != 0)
                        {
                            valid = 0;
                            break;
                        }
                        int dropPos = i + 2 * L - 1 - k;
                        const char *sDrop = lines[dropPos];
                        while (*sDrop && isspace((unsigned char)*sDrop))
                            sDrop++;
                        if (strncmp(sDrop, "drop(", 5) != 0)
                        {
                            valid = 0;
                            break;
                        }
                        if (match[i + k] != dropPos)
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (valid)
                        best = L;
                    else
                        break;
                }
                if (best > 0)
                {
                    for (j = i; j < i + 2 * best; j++)
                        used[j] = 1;
                    for (k = 0; k < best; k++)
                    {
                        printIndent(k);
                        printf("{\n");
                    }
                    for (k = 0; k < best; k++)
                    {
                        printIndent(k + 1);
                        printf("%s\n", lines[i + k]);
                    }
                    for (k = best - 1; k >= 0; k--)
                    {
                        printIndent(k);
                        printf("}\n");
                    }
                    continue;
                }
                printf("%s\n", lines[i]);
            }
            else
            {
                printf("%s\n", lines[i]);
            }
        }
    }
    for (i = 0; i < n; i++)
        free(lines[i]);
    return 0;
}