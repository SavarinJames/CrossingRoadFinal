#include "header.h"

using namespace std;

int main()
{
	system("cls");
	srand(time(NULL));
	setConsoleSize();
	FixConsoleWindow();
	hidecursor();
	//cin >>  x >>  y;
	drawMap(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	CGAME game(5);
	int t = 100;
	int dir;
	while (t--)
	{
		dir = toupper(getch());
		if (!game.getPeople().isDead())
		{
			game.updatePosPeople(dir);
			game.updatePosVehicle();
			game.updatePosAnimal();
			game.drawGame();
			int impCordX, impCordY;

			vector<CVEHICLE *> vehicles = game.getVehicle();
			vector<CANIMAL *> animals = game.getAnimal();
			if (game.getPeople().isImpact(vehicles, impCordX, impCordY) || game.getPeople().isImpact(animals, impCordX, impCordY))
			{
				GotoXY(impCordX, impCordY);
				cout << char(178);
				system("pause");
				// ...
			}
		}
	}
	Sleep(100);
}