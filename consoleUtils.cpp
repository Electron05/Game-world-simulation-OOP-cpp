#include "consoleUtils.h"
#include <Windows.h>
#include <stdlib.h>


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clrscr() {
    system("cls");
}
void changeColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void changeCursorVisibility(bool visible) {
    CONSOLE_CURSOR_INFO consoleCursor;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &consoleCursor);
    consoleCursor.bVisible = visible;
    SetConsoleCursorInfo(hConsole, &consoleCursor);
}