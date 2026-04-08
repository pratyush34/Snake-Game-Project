#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void saveScore(char *name, int score);
void showLeaderboard();

void gotoxy(int x, int y) {
  COORD p;
  p.X = x;
  p.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void boundary() {
  int x = 119, y = 28;
  printf("%c", 218);
  for (int i = 1; i < x; i++) {
    printf("%c", 196);
  }
  printf("%c", 191);
  for (int i = 1; i < y; i++) {
    gotoxy(x, i);
    printf("%c", 179);
    gotoxy(0, i);
    printf("%c", 179);
  }
  printf("\n%c", 192);
  for (int i = 1; i < x; i++) {
    printf("%c", 196);
  }
  printf("%c", 217);
  gotoxy(0, 0);
}

void over(int, int, int, char *);

void move(int *x, int *y, char *l, char c, int len) {
  gotoxy(x[len - 1], y[len - 1]);
  printf(" ");
  for (int i = len; i > 0; i--) {
    x[i] = x[i - 1];
    y[i] = y[i - 1];
  }
  *l = c;
  if (len > 1) {
    gotoxy(x[1], y[1]);
    printf("o");
  }
}

int check(int px, int py, int *x, int *y, int len) {
  for (int i = 0; i < len; i++) {
    if (px == x[i] && py == y[i])
      return 1;
  }
  return 0;
}

void game(char *name) {
  srand(time(NULL));
  int *x, *y, px = ((rand() % 57) * 2) + 3, py = (rand() % 27) + 1, len = 1;
  char c, l;
  clock_t t;
  int speed = 250;

  x = (int *)malloc(len * sizeof(int) * (len + 1));
  y = (int *)malloc(len * sizeof(int) * (len + 1));
  x[0] = 25;
  y[0] = 20;

  gotoxy(102, 1);
  printf("s c o r e : 0 0");

  gotoxy(px, py);
  printf("%c", 254);

  gotoxy(x[0], y[0]);
  printf("%c", 154);

  while (1) {
    do {
      t = clock();
      while (clock() < t + speed && !kbhit())
        ;
      if (clock() < t + speed) {
        c = getch();
        if (c == 'a' && l == 'd')
          c = 'd';
        else if (c == 'd' && l == 'a')
          c = 'a';
        else if (c == 'w' && l == 's')
          c = 's';
        else if (c == 's' && l == 'w')
          c = 'w';
      }
      switch (c) {
      case 0:
        break;
      case 13:
        break;
      case 's':
        move(x, y, &l, c, len);
        gotoxy(x[0], ++y[0]);

        printf("%c", 153);
        if (y[0] >= 28) {
          over(x[0], y[0], len, name);
        }
        break;
      case 'w':
        move(x, y, &l, c, len);
        gotoxy(x[0], --y[0]);
        printf("%c", 153);
        if (y[0] <= 0) {
          over(x[0], y[0], len, name);
        }
        break;
      case 'a':
        move(x, y, &l, c, len);
        gotoxy(x[0] = x[0] - 2, y[0]);
        printf("%c", 153);
        if (x[0] <= 0) {
          over(x[0], y[0], len, name);
        }
        break;
      case 'd':
        move(x, y, &l, c, len);
        gotoxy(x[0] = x[0] + 2, y[0]);
        printf("%c", 153);
        if (x[0] >= 119) {
          over(x[0], y[0], len, name);
        }
        break;
      default:
        break;
      }
      movingSound();

      for (int i = 4; i < len; i++) {
        if (x[0] == x[i] && y[0] == y[i]) {
          over(x[0], y[0], len, name);
        }
      }
      for (int i = 4; i < len; i++) {
        if (x[0] == x[i] && y[0] == y[i]) {
          over(x[0], y[0], len, name);
        }
      }

    } while (x[0] != px || y[0] != py);

    gotoxy(x[len], y[len]);
    munchSound();
    printf("o");
    len++;

    gotoxy(114, 1);
    printf("%d %d", (len - 1) / 10, (len - 1) % 10);

    if (speed >= 70)
      speed -= 10;

    x = (int *)realloc(x, sizeof(int) * (len + 1));
    y = (int *)realloc(y, sizeof(int) * (len + 1));

    do {
      px = ((rand() % 57) * 2) + 3, py = (rand() % 27) + 1;
    } while (check(px, py, x, y, len));

    gotoxy(px, py);
    printf("%c", 254);
  }
}

void over(int x, int y, int len, char *name) {
  gotoxy(x, y);
  printf("x");
  deathSound();
  gotoxy(1, 1);
  printf("GAME OVER!\n");
  printf("%cScore : %d \n", 179, len - 1);
  saveScore(name, len - 1);
  showLeaderboard();
  printf("%cDo you want to retry? (Y/N)", 179);
  char c;
  while (1) {
    c = getch();
    if (c == 'Y' || c == 'y') {
      system("cls");
      boundary();
      game(name);
    } else if (c == 'N' || c == 'n') {
      exit(0);
    } else {
      continue;
    }
  }
}
