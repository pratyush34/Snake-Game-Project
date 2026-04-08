#include <conio.h>
#include <stdio.h>
#include <windows.h>

void setColor(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawBanner() {
  setColor(10);
  printf("====================================================================="
         "======\n");
  setColor(14);
  printf("   ____  _   _    _    _  _______   ____  ____  _____ ____ _____ ___ "
         "____ _____\n");
  printf("  / ___|| \\ | |  / \\  | |/ / ____| |  _ \\|  _ \\| ____/ ___|_   "
         "_|_ _/ ___| ____|\n");
  printf("  \\___ \\|  \\| | / _ \\ | ' /|  _|   | |_) | |_) |  _| \\___ \\ | "
         "|  | | |  _|  _|  \n");
  printf("   ___) | |\\  |/ ___ \\| . \\| |___  |  __/|  _ <| |___ ___) || |  "
         "| | |_| | |___ \n");
  printf("  |____/|_| \\_/_/   \\_\\_|\\_\\_____| |_|   |_| \\_\\_____|____/ "
         "|_| |___\\____|_____|\n");
  setColor(10);
  printf("====================================================================="
         "======\n");
  setColor(7);
}

void drawFooter() {
  setColor(11);
  printf("\n\t[ W/S: Navigate ] [ ENTER: Select ]\n");
  setColor(7);
}

void splashScreen() {
  drawBanner();
  drawFooter();
}

void movingSound() { Beep(250, 15); }

void playBGM() {
  mciSendString("close bgm", NULL, 0, NULL);
  mciSendString("open \"sounds/bgm.mp3\" type mpegvideo alias bgm", NULL, 0,
                NULL);
  mciSendString("play bgm repeat", NULL, 0, NULL);
}

void stopBGM() { mciSendString("close bgm", NULL, 0, NULL); }

void playSelect() {
  mciSendString("close select", NULL, 0, NULL);
  mciSendString("open \"sounds/select.mp3\" type mpegvideo alias select", NULL,
                0, NULL);
  mciSendString("play select", NULL, 0, NULL);
}

void munchSound() {
  mciSendString("close munch", NULL, 0, NULL);
  mciSendString("open \"sounds/munch.mp3\" type mpegvideo alias munch", NULL, 0,
                NULL);
  mciSendString("play munch", NULL, 0, NULL);
}

void deathSound() {
  mciSendString("close death", NULL, 0, NULL);
  mciSendString("open \"sounds/death.mp3\" type mpegvideo alias death", NULL, 0,
                NULL);
  mciSendString("play death", NULL, 0, NULL);
}
int mainMenu() {
  int choice = 1;
  const int totalOptions = 4;
  char key;

  while (1) {
    system("cls");
    drawBanner();

    printf("\n\n");

    if (choice == 1)
      setColor(10);
    else
      setColor(15);
    printf("\t\t%s [1] START\n", (choice == 1 ? ">>" : "  "));

    if (choice == 2)
      setColor(10);
    else
      setColor(15);
    printf("\t\t%s [2] LEADERBOARD\n", (choice == 2 ? ">>" : "  "));

    if (choice == 3)
      setColor(10);
    else
      setColor(15);
    printf("\t\t%s [3] CHANGE PASSWORD\n", (choice == 3 ? ">>" : "  "));

    if (choice == 4)
      setColor(12);
    else
      setColor(15); // Red for exit
    printf("\t\t%s [4] EXIT\n", (choice == 4 ? ">>" : "  "));

    drawFooter();

    key = getch();
    if (key == 'w' || key == 'W') {
      choice = (choice == 1) ? totalOptions : choice - 1;
    } else if (key == 's' || key == 'S') {
      choice = (choice == totalOptions) ? 1 : choice + 1;
    } else if (key == 13) {
      playSelect();
      return choice;
    }
  }
}
