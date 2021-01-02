#include "header.h"

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
	RECT rect = {100, 100, 1150, 650};
	MoveWindow(consoleWindow, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

void drawMap(int width, int height, int level)
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
	GotoXY(width + 10, 4);
	cout << FYEL("^^^CROSSING ROAD^^^");
	GotoXY(width + 16, 6);
	cout << FGRN("LEVEL ") << level;
	GotoXY(width + 2, 6);
	//cout << FRED("Please Pause before load/save game");
	//GotoXY(WIDTH + 8, 8); cout << "	";
	GotoXY(width + 10, 12);
	cout << FMAG("P: Pause/Resume");
	GotoXY(width + 10, 14);
	cout << FCYN("K: Save");
	GotoXY(width + 10, 16);
	cout << FRED("L: Load");
	GotoXY(width + 10, 18);
	cout << FBLU("ESC: Return");
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

void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void menu()
{
	system("cls");
	GotoXY(10, 0);
	cout << R"(     _____   ____________________________________________________________________________________________________)"
		 << "\n";
	GotoXY(10, 1);
	cout << R"(    /  __ \                                                                                                      |)"
		 << "\n";
	GotoXY(10, 2);
	cout << R"(    | /  \/_ __ ___  ___ ___                                                                                     |)"
		 << "\n";
	GotoXY(10, 3);
	cout << R"(    | |   | '__/ _ \/ __/ __|                                                                                    |)"
		 << "\n";
	GotoXY(10, 4);
	cout << R"(    | \__/\ | | (_) \__ \__ \                                                                                    |)"
		 << "\n";
	GotoXY(10, 5);
	cout << R"(     \____/_|  \___/|___/___/                                                                                    |)"
		 << "\n";
	GotoXY(10, 6);
	cout << R"(    ______                _                                                                                      |)"
		 << "\n";
	GotoXY(10, 7);
	cout << R"(    | ___ \              | |                                                                                     |)"
		 << "\n";
	GotoXY(10, 8);
	cout << R"(    | |_/ /___   __ _  __| |                                                                                     |)"
		 << "\n";
	GotoXY(10, 9);
	cout << R"(    |    // _ \ / _` |/ _` |                                                                                     |)"
		 << "\n";
	GotoXY(10, 10);
	cout << R"(    | |\ \ (_) | (_| | (_| |                                                                                     |)"
		 << "\n";
	GotoXY(10, 11);
	cout << R"(    \_| \_\___/ \__,_|\__,_|                                                                                     |)";
	GotoXY(10, 12);
	cout << R"(                                                                                                                 |)";
	GotoXY(10, 13);
	cout << R"(                                                                                                                 |)";
	GotoXY(10, 14);
	cout << R"(                                                                                                                 |)";
	GotoXY(10, 15);
	cout << R"(                                                                                                                 |)";
	GotoXY(10, 16);
	cout << R"(                                                                                                                 |)";
	GotoXY(10, 17);
	cout << R"(                                                                                                                 |)";

	// system("cls");
	GotoXY(54, 10);
	cout << " ___________________________";
	GotoXY(54, 11);
	cout << "|                           |";
	GotoXY(54, 12);
	cout << "|                           |";
	GotoXY(54, 13);
	cout << "|                           |";
	GotoXY(54, 14);
	cout << "|                           |";
	GotoXY(54, 15);
	cout << "|                           |";
	GotoXY(54, 16);
	cout << "|                           |";
	GotoXY(54, 17);
	cout << "|                           |";
	GotoXY(54, 18);
	cout << "|                           |";
	GotoXY(54, 19);
	cout << "|___________________________|";

	GotoXY(55, 12);
	cout << FRED("       1. NEW GAME.      ");

	GotoXY(55, 14);
	cout << FBLU("       2. LOAD GAME.     ");

	GotoXY(55, 16);
	cout << FGRN("       3. SETTINGS.      ");

	GotoXY(55, 18);
	cout << FMAG("       4. QUIT.          ");

	GotoXY(95, 10);
	GotoXY(95, 18);
	cout << R"(     _____                  |)"
		 << "\n";
	GotoXY(95, 19);
	cout << R"(    /  __ \                 |)"
		 << "\n";
	GotoXY(95, 20);
	cout << R"(    | /  \/_ __ ___  ___ ___ )"
		 << "\n";
	GotoXY(95, 21);
	cout << R"(    | |   | '__/ _ \/ __/ __|)"
		 << "\n";
	GotoXY(95, 22);
	cout << R"(    | \__/\ | | (_) \__ \__ \)"
		 << "\n";
	GotoXY(95, 23);
	cout << R"(     \____/_|  \___/|___/___/)"
		 << "\n";
	GotoXY(95, 24);
	cout << R"(    ______                _ )"
		 << "\n";
	GotoXY(95, 25);
	cout << R"(    | ___ \              | |)"
		 << "\n";
	GotoXY(95, 26);
	cout << R"(    | |_/ /___   __ _  __| |)"
		 << "\n";
	GotoXY(95, 27);
	cout << R"(    |    // _ \ / _` |/ _` |)"
		 << "\n";
	GotoXY(95, 28);
	cout << R"(    | |\ \ (_) | (_| | (_| |)"
		 << "\n";
	GotoXY(95, 29);
	cout << R"(    \_| \_\___/ \__,_|\__,_|)";
	// GotoXY(10, 29); cout << R"(                                                                                                                 |)";
	GotoXY(10, 29);
	cout << R"(    _____________________________________________________________________________________)";
	for (int i = 29; i >= 13; --i)
	{
		GotoXY(14, i);
		cout << "|";
	}
	hidecursor();
}
