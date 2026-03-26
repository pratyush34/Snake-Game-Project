#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "gamePlay.c"
#include "auth.c"

int main() // huehueheu
{
    system("mode con: cols=120 lines=30");
    char name[50];
    login(name);
    game(name);
    return 0;
}