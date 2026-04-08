#include "aaextra.c"
#include "auth.c"
#include "gamePlay.c"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <windows.h>

int main() {
  system("mode con: cols=120 lines=30");
  char name[50];

  splashScreen();
  playBGM();
  login(name);

  while (1) {
    int selection = mainMenu(); 

    switch (selection) {
    case 1:
      stopBGM();
      game(name);
      break;
    case 2:
      system("cls");
      showLeaderboard();
      printf("\n\tPress any key to return...");
      getch();
      break;
    case 3:
      changePasswordUI(name);
      break;
    case 4:
      exit(0);
    }
  }
  return 0;
}
