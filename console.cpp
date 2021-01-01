#include "header.h"

using namespace std;

void FixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setConsoleSize()
{
    HWND consoleWindow = GetConsoleWindow();
    RECT rect = {100, 100, 1350, 700};
    MoveWindow(consoleWindow, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

void drawMap(int width, int height)
{
    GotoXY(1, 0);
    for (int x = 1; x < width; x++)
        cout << char(95);

    GotoXY(1, height - 1);
    for (int x = 1; x < width; x++)
        cout << char(95); // ___

    for (int y = 1; y < height; y++)
    {
        GotoXY(0, y);
        cout << char(124);
    }

    for (int y = 1; y < height; y++)
    {
        GotoXY(width, y);
        cout << char(124); // ||
    }

    for (int lanes = 1; lanes <= 6; lanes++)
    {
        GotoXY(1, 5 * lanes);
        for (int x = 1; x < width; x++)
            cout << char(95);
    }
}

void cls()
{
    cout.flush();
    string filler(CONSOLE_WIDTH - 1, ' ');
    int cordX = 1, cordY = 1;
    for (cordY = 1; cordY < CONSOLE_HEIGHT; cordY++)
        if (cordY % 5)
        {
            GotoXY(cordX, cordY);
            cout << filler;
        }
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void menu() {
    system("cls");
    GotoXY(50, 10);  cout <<"   1. New Game.";
    GotoXY(50, 11);  cout <<"   2. Load game.";
    GotoXY(50, 12);  cout <<"   3. Settings.";
    GotoXY(50, 13);  cout <<"   4. Quit.";
}
