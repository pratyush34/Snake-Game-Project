#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readPassword(char *pass) {
  int i = 0;
  char c;
  while ((c = getch()) != '\r') {
    if (c == '\b') {
      if (i > 0) {
        i--;
        printf("\b \b");
        fflush(stdout);
      }
    } else if (i < 49) {
      pass[i++] = c;
      printf("*");
      fflush(stdout);
    }
  }
  pass[i] = '\0';
  printf("\n");
}

void login(char *name) {
  printf("ENTER YOUR USERNAME : ");
  fflush(stdout);
  scanf("%s", name);

  FILE *f = fopen("data.txt", "a+");
  char line[50], pass[50];
  int score, found = 0;
  rewind(f);

  while (fscanf(f, "%[^,],%[^,],%d\n", line, pass, &score) == 3) {
    if (strcmp(line, name) == 0) {
      found = 1;
      int attempts = 3;
      int ok = 0;
      while (attempts--) {
        char entered[50];
        printf("ENTER PASSWORD : ");
        fflush(stdout);
        readPassword(entered);

        if (strcmp(entered, pass) == 0) {
          ok = 1;
          break;
        } else {
          printf("Wrong password! %d attempt(s) left.\n", attempts);
          fflush(stdout);
        }
      }

      if (!ok) {
        printf("Too many wrong attempts. Exiting.\n");
        fflush(stdout);
        fclose(f);
        getch();
        exit(1);
      }

      printf("Welcome back %s! Your last score : %d\n", name, score);
      fflush(stdout);
      break;
    }
  }

  if (!found) {
    char newpass[50], confirm[50];

    printf("New user! Create a password : ");
    fflush(stdout);
    readPassword(newpass);

    printf("Confirm password : ");
    fflush(stdout);
    readPassword(confirm);

    while (strcmp(newpass, confirm) != 0) {
      printf("Passwords do not match! Try again.\n");
      fflush(stdout);

      printf("Create a password : ");
      fflush(stdout);
      readPassword(newpass);

      printf("Confirm password  : ");
      fflush(stdout);
      readPassword(confirm);
    }

    fprintf(f, "%s,%s,0\n", name, newpass);
    printf("Welcome %s! Password saved.\n", name);
    fflush(stdout);
  }

  fclose(f);
}

void saveScore(char *name, int score) {
  FILE *f = fopen("data.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  char line[50], pass[50];
  int s;

  while (fscanf(f, "%[^,],%[^,],%d\n", line, pass, &s) == 3) {
    if (strcmp(line, name) == 0 && score > s)
      fprintf(temp, "%s,%s,%d\n", name, pass, score);
    else
      fprintf(temp, "%s,%s,%d\n", line, pass, s);
  }

  fclose(f);
  fclose(temp);
  remove("data.txt");
  rename("temp.txt", "data.txt");
}

void showLeaderboard() {
  FILE *f = fopen("data.txt", "r");
  char names[100][50], passes[100][50];
  int scores[100], count = 0;

  while (fscanf(f, "%[^,],%[^,],%d\n", names[count], passes[count],
                &scores[count]) == 3)
    count++;
  fclose(f);

  for (int i = 0; i < count - 1; i++)
    for (int j = 0; j < count - i - 1; j++)
      if (scores[j] < scores[j + 1]) {
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

// added functions

void changePasswordUI(char *name) {
  char newPass[50];
  system("cls");

  setColor(14);
  printf("\n\t    CHANGE PASSWORD    \n");
  setColor(11);
  printf("\tUser: %s\n", name);
  setColor(15);
  printf("\tEnter new password: ");

  scanf("%s", newPass);

  FILE *f = fopen("data.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  char user[50], pass[50];
  int score;

  while (fscanf(f, "%[^,],%[^,],%d\n", user, pass, &score) == 3) {
    if (strcmp(user, name) == 0) {
      fprintf(temp, "%s,%s,%d\n", user, newPass, score);
    } else {
      fprintf(temp, "%s,%s,%d\n", user, pass, score);
    }
  }
  fclose(f);
  fclose(temp);

  remove("data.txt");
  rename("temp.txt", "data.txt");

  setColor(10);
  printf("\n\tPassword successfully updated!");
  setColor(7);
  printf("\n\tPress any key to return...");
  getch();
}
