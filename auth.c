#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void readPassword(char *pass)
{
    int i = 0;
    char c;
    while ((c = getch()) != '\r') /* '\r' = Enter key */
    {
        if (c == '\b') /* Backspace */
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); /* erase last * on screen */
                fflush(stdout);
            }
        }
        else if (i < 49) /* max 49 chars */
        {
            pass[i++] = c;
            printf("*");
            fflush(stdout);
        }
    }
    pass[i] = '\0';
    printf("\n");
}

void login(char *name)
{
    system("cls");
    boundary();
    gotoxy(1, 1);
    printf("</SNAKE GAME>\n");

    /* --- Get username --- */
    printf("%cENTER YOUR USERNAME : ", 179);
    fflush(stdout);
    scanf("%s", name);

    /* --- Search in file --- */
    FILE *f = fopen("data.txt", "a+");
    char line[50], pass[50];
    int score, found = 0;
    rewind(f);

    while (fscanf(f, "%[^,],%[^,],%d\n", line, pass, &score) == 3)
    {
        if (strcmp(line, name) == 0)
        {
            found = 1;

            /* --- Returning user: ask password (3 attempts) --- */
            int attempts = 3;
            int ok = 0;
            while (attempts--)
            {
                char entered[50];
                printf("%cENTER PASSWORD : ", 179);
                fflush(stdout);
                readPassword(entered);

                if (strcmp(entered, pass) == 0)
                {
                    ok = 1;
                    break;
                }
                else
                {
                    printf("%cWrong password! %d attempt(s) left.\n",
                           179, attempts);
                    fflush(stdout);
                }
            }

            if (!ok)
            {
                printf("%cToo many wrong attempts. Exiting.\n", 179);
                fflush(stdout);
                fclose(f);
                getch();
                exit(1);
            }

            printf("%cWelcome back %s! Your last score : %d\n",
                   179, name, score);
            fflush(stdout);
            break;
        }
    }

    /* --- New user: create password --- */
    if (!found)
    {
        char newpass[50], confirm[50];

        printf("%cNew user! Create a password : ", 179);
        fflush(stdout);
        readPassword(newpass);

        printf("%cConfirm password       : ", 179);
        fflush(stdout);
        readPassword(confirm);

        /* Keep asking until passwords match */
        while (strcmp(newpass, confirm) != 0)
        {
            printf("%cPasswords do not match! Try again.\n", 179);
            fflush(stdout);

            printf("%cCreate a password : ", 179);
            fflush(stdout);
            readPassword(newpass);

            printf("%cConfirm password  : ", 179);
            fflush(stdout);
            readPassword(confirm);
        }

        fprintf(f, "%s,%s,0\n", name, newpass);
        printf("%cWelcome %s! Password saved.\n", 179, name);
        fflush(stdout);
    }

    fclose(f);
    printf("%cUse W, A, S & D for movements.\n", 179);
    printf("%cEnter any key to continue.", 179);
    getch();
    system("cls");
    boundary();
}

void saveScore(char *name, int score)
{
    FILE *f = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[50], pass[50];
    int s;

    while (fscanf(f, "%[^,],%[^,],%d\n", line, pass, &s) == 3)
    {
        if (strcmp(line, name) == 0)
            fprintf(temp, "%s,%s,%d\n", name, pass, score);
        else
            fprintf(temp, "%s,%s,%d\n", line, pass, s);
    }

    fclose(f);
    fclose(temp);
    remove("data.txt");
    rename("temp.txt", "data.txt");
}

void showLeaderboard()
{
    FILE *f = fopen("data.txt", "r");
    char names[100][50], passes[100][50];
    int scores[100], count = 0;

    while (fscanf(f, "%[^,],%[^,],%d\n",
                  names[count], passes[count], &scores[count]) == 3)
        count++;
    fclose(f);

    /* bubble sort descending by score */
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (scores[j] < scores[j + 1])
            {
                int tmp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tmp;

                char t[50];
                strcpy(t, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], t);

                strcpy(t, passes[j]);
                strcpy(passes[j], passes[j + 1]);
                strcpy(passes[j + 1], t);
            }

    printf("\n%c=== LEADERBOARD ===\n", 179);
    for (int i = 0; i < count && i < 5; i++)
        printf("%c%d. %s - %d\n", 179, i + 1, names[i], scores[i]);
}