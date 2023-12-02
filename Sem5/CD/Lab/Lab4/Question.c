#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int present(char a[], char ch);
int check(char nt, char t, char cfg[100][100], int len1);

int main()
{
    FILE *fp;
    char str[100];
    int non_terminals = 0;
    int terminals = 0;
    char nt[10];
    char t[10];
    int k = 0;
    int l = 0;
    int max = 0;
    int len = 0;
    int len1 = 0;
    int temp = 0;

    fp = fopen("cfg.txt", "r");

    while (fgets(str, 50, fp) != NULL)
    {
        // printf("%s\n",str);
        len = 0;
        len1++;
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] >= 65 && str[i] <= 90)
            {
                temp = 0;
                for (int k1 = 0; k1 < k; k1++)
                {
                    if (nt[k1] == str[i])
                    {
                        temp = 1;
                        break;
                    }
                }
                if (temp == 0)
                {
                    nt[k] = str[i];
                    k++;
                }
                len++;
            }
            if (str[i] >= 97 && str[i] <= 122)
            {
                temp = 0;
                for (int k1 = 0; k1 < l; k1++)
                {
                    if (t[k1] == str[i])
                    {
                        temp = 1;
                        break;
                    }
                }
                if (temp == 0)
                {
                    t[l] = str[i];
                    l++;
                }
                len++;
            }
            if (str[i] == '$')
            {
                temp = 0;
                for (int k1 = 0; k1 < l; k1++)
                {
                    if (t[k1] == str[i])
                    {
                        temp = 1;
                        break;
                    }
                }
                if (temp == 0)
                {
                    t[l] = str[i];
                    l++;
                }

                len++;
            }
        }

        if (len >= max)
        {
            max = len;
        }
    }

    terminals = l;
    non_terminals = k;

    rewind(fp);

    char cfg[100][100];
    k = 0;

    while (fgets(str, 50, fp) != NULL)
    {
        l = 0;
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] >= 65 && str[i] <= 90)
            {
                cfg[k][l] = str[i];
                l++;
            }
            else if (str[i] >= 97 && str[i] <= 122)
            {
                cfg[k][l] = str[i];
                l++;
            }
            else if (str[i] == '$')
            {
                cfg[k][l] = str[i];
                l++;
            }
        }
        k++;
    }

    // printf("Given CFG is : \n");
    // for (int i = 0; i < len1; i++)
    // {
    //     for (int j = 0; j < max; j++)
    //     {
    //         printf(" %c ", cfg[i][j]);
    //     }
    //     printf("\n");
    // }

    int ll1_table[non_terminals][terminals];

    for (int i = 0; i < non_terminals; i++)
    {
        for (int j = 0; j < terminals; j++)
        {
            ll1_table[i][j] = check(nt[i], t[j], cfg, len1);
        }
    }

    for (int i = 0; i < non_terminals; i++)
    {
        for (int j = 0; j < terminals; j++)
        {
            int z = ll1_table[i][j];

            if (z == -1)
            {
                printf("%c cannot generate %c\n", nt[i], t[j]);
            }
            else
            {
                printf("%c can generate %c by production : ", nt[i],t[j]);
                for (int k = 0; k < max; k++)
                {
                    printf(" %c ",cfg[z][k]);
                    if(k == 0) {
                        printf(" -> ");
                    }
                }
                printf("\n");
            }
        }
        printf("\n");
    }

    return 0;
}

int present(char a[], char ch)
{
    for (int i = 0; i < strlen(a); i++)
    {
        if (a[i] == ch)
        {
            return 1;
        }
    }
    return 0;
}

int check(char nt, char t, char cfg[100][100], int k1)
{
    int val = -1;

    for (int i = 0; i < k1; i++)
    {
        if (cfg[i][0] == nt)
        {
            if (cfg[i][1] == t)
            {

                return i;
            }
            else
            {
                val = check(cfg[i][1], t, cfg, k1);

                if (val != -1)
                {
                    return i;
                }
            }
        }
    }

    if (val != -1)
        return val;
    return -1;
}