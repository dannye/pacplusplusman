#include <Windows.h>

#include "Constants.h"

void SetWindowTitle(char title[]) {
    SetConsoleTitle(title);
}

void SetWindowSize(int height, int width) {
    SMALL_RECT window;
    window.Top = 0;
    window.Left = 0;
    window.Bottom = height - 1;
    window.Right = width - 1;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &window);
    COORD buffer = {width,height};
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buffer);
}

void SetCursorVisibility(bool show) {
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    cursor.bVisible = show;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void SetCursorPosition(int y, int x) {
    COORD cursor = {x,y+3};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

void SetTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetScreenColor(int color) {
    COORD coord = {0,3};
    DWORD dwWritten;
    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color, LEVEL_HEIGHT * LEVEL_WIDTH, coord, &dwWritten);
}
