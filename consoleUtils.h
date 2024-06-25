#pragma once
#define GREEN 10
#define DARK_GREEN 2
#define DARK_RED 4
#define DEFAULT 15
#define YELLOW 14
#define RED 12
#define GRAY 8
void gotoxy(int x, int y);
void clrscr();
void changeColor(int color);
void changeCursorVisibility(bool visible);