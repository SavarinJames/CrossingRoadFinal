#include "header.h"

CGAME::CGAME()
{
	resetGame(1);
}

void CGAME::flipTruckLight()
{
	truckLight.lightSwitch();
}

void CGAME::flipCarLight()
{
	carLight.lightSwitch();
}

void CGAME::startGame()
{
	system("cls");
	resetGame(1);
	drawMap(CONSOLE_WIDTH, CONSOLE_HEIGHT, 1);
	drawGame();
}

void CGAME::resetGame(int lev)
{
	deleteMovingObj();

	cls();

	human.revive();

	shuffleLanes();
	level = lev;
	int maxObj = lev * 1;
	int randNum;
	int beginX;
	int lightCordX, lightCordY;
	bool leftSide;

	// for Trucks
	randNum = rand() % maxObj + 3;
	leftSide = rand() % 2;
	if (leftSide)
		lightCordX = 2;
	else
		lightCordX = CONSOLE_WIDTH - 2;
	lightCordY = ground + 5 * lanes[1] - 3; // light for trucks
	truckLight.setCord(lightCordX, lightCordY);
	beginX = 0;
	while (randNum--)
	{
		beginX += rand() % (CONSOLE_WIDTH / maxObj) + 3;
		if (beginX > CONSOLE_WIDTH - 3)
			break;
		CTRUCK *newTruck = new CTRUCK(beginX, ground + 5 * lanes[1], leftSide);
		trucks.push_back(newTruck);
	}

	// for Cars
	randNum = rand() % maxObj + 3;
	leftSide = rand() % 2;
	if (leftSide)
		lightCordX = 2;
	else
		lightCordX = CONSOLE_WIDTH - 2;
	lightCordY = ground + 5 * lanes[2] - 3; // light for cars
	carLight.setCord(lightCordX, lightCordY);
	beginX = 0;
	while (randNum--)
	{
		beginX += rand() % (CONSOLE_WIDTH / maxObj) + 3;
		if (beginX > CONSOLE_WIDTH - 3)
			break;
		CCAR *newCar = new CCAR(beginX, ground + 5 * lanes[2], leftSide);
		cars.push_back(newCar);
	}

	// for Dinos
	randNum = rand() % maxObj + 3;
	leftSide = rand() % 2;
	beginX = 0;
	while (randNum--)
	{
		beginX += rand() % (CONSOLE_WIDTH / maxObj) + 3;
		if (beginX > CONSOLE_WIDTH - 3)
			break;
		CDINOSAUR *newDino = new CDINOSAUR(beginX, ground + 5 * lanes[3], leftSide);
		dinos.push_back(newDino);
	}

	// for Birds
	randNum = rand() % maxObj + 3;
	leftSide = rand() % 2;
	beginX = 0;
	while (randNum--)
	{
		beginX += rand() % (CONSOLE_WIDTH / maxObj) + 3;
		if (beginX > CONSOLE_WIDTH - 3)
			break;
		CBIRD *newBird = new CBIRD(beginX, ground + 5 * lanes[4], leftSide);
		birds.push_back(newBird);
	}
}

void CGAME::shuffleLanes()
{
	int t = 16;
	while (t--)
	{
		int id1 = rand() % 4 + 1;
		int id2 = rand() % 4 + 1;
		swap(lanes[id1], lanes[id2]);
	}
}

CPEOPLE CGAME::getPeople()
{
	return human;
}

vector<CVEHICLE *> CGAME::getVehicle()
{
	vector<CVEHICLE *> vehicles;
	for (int i = 0; i < trucks.size(); i++)
	{
		CVEHICLE *p = trucks[i];
		vehicles.push_back(p);
	}
	for (int i = 0; i < cars.size(); i++)
	{
		CVEHICLE *p = cars[i];
		vehicles.push_back(p);
	}
	return vehicles;
}

vector<CANIMAL *> CGAME::getAnimal()
{
	vector<CANIMAL *> animals;
	for (int i = 0; i < birds.size(); i++)
	{
		CANIMAL *p = birds[i];
		animals.push_back(p);
	}
	for (int i = 0; i < dinos.size(); i++)
	{
		CANIMAL *p = dinos[i];
		animals.push_back(p);
	}
	return animals;
}

void CGAME::updatePosVehicle()
{
	if (truckLight.canGo())
		for (int i = 0; i < trucks.size(); i++)
			trucks[i]->move();
	if (carLight.canGo())
		for (int i = 0; i < cars.size(); i++)
			cars[i]->move();
}

void CGAME::updatePosAnimal()
{
	for (int i = 0; i < birds.size(); i++)
		birds[i]->move();
	for (int i = 0; i < dinos.size(); i++)
		dinos[i]->move();
}

void CGAME::updatePosPeople(int direction)
{
	switch (direction)
	{
	case ('W'):
		human.Up();
		break;
	case ('A'):
		human.Left(1);
		break;
	case ('S'):
		human.Down();
		break;
	case ('D'):
		human.Right(1);
		break;
	default:
		break;
	}
}

void CGAME::drawGame()
{
	cls();

	truckLight.draw();
	for (int i = 0; i < trucks.size(); i++)
		trucks[i]->draw();
	carLight.draw();
	for (int i = 0; i < cars.size(); i++)
		cars[i]->draw();

	for (int i = 0; i < dinos.size(); i++)
		dinos[i]->draw();
	for (int i = 0; i < birds.size(); i++)
		birds[i]->draw();

	human.draw();

	//Sleep(100 / (5 * level)); // increases the speed of the objects
}

void CGAME::deleteMovingObj()
{
	for (int i = 0; i < trucks.size(); i++)
		delete trucks[i];
	for (int i = 0; i < cars.size(); i++)
		delete cars[i];
	for (int i = 0; i < dinos.size(); i++)
		delete dinos[i];
	for (int i = 0; i < birds.size(); i++)
		delete birds[i];
	trucks.clear();
	cars.clear();
	dinos.clear();
	birds.clear();
}

CGAME::~CGAME()
{
	deleteMovingObj();
}

void ImpactEffect(int x, int y)
{
	GotoXY(x + 3, y - 3);
	cout << FGRN("OOPS!!$%");
	GotoXY(x + 3, y - 2);
	cout << FGRN("  @~^");
	Sleep(500);
	GotoXY(x + 3, y - 3);
	cout << FYEL("OOPS!!$%");
	GotoXY(x + 3, y - 2);
	cout << FYEL("  @~^");
	Sleep(300);
	mciSendString(TEXT("play crash.mp3 "), NULL, 0, NULL);
	GotoXY(x + 3, y - 3);
	cout << FRED("OOPS!!$%");
	GotoXY(x + 3, y - 2);
	cout << FRED("  @~^");
}
void loseboard(int level)
{
	system("cls");
	GotoXY(53, 10);
	cout << FCYN(" _____________________________");
	GotoXY(53, 11);
	cout << FCYN("|                             |");
	GotoXY(53, 12);
	cout << FCYN("|                             |");
	GotoXY(53, 13);
	cout << FCYN("|                             |");
	GotoXY(53, 14);
	cout << FCYN("|                             |");
	GotoXY(53, 15);
	cout << FCYN("|                             |");
	GotoXY(53, 16);
	cout << FCYN("|                             |");
	GotoXY(53, 17);
	cout << FCYN("|                             |");
	GotoXY(53, 18);
	cout << FCYN("|                             |");
	GotoXY(53, 19);
	cout << FCYN("|_____________________________|");
	GotoXY(54, 13);
	cout << "     YOU LOSE AT LEVEL " << level;

	GotoXY(54, 15);
	cout << "       Press any key ";
	GotoXY(54, 16);
	cout << "       to back Menu.";
}
void winboard()
{
	system("cls");
	GotoXY(45, 13);
	cout << FGRN("XXXXXX  XXXXXX  X    X  XXXXX  XXXX      XX    XXXXX  XXXX");
	GotoXY(45, 14);
	cout << FGRN("X       X    X  X X  X  X      X   X    X  X     X     X  ");
	GotoXY(45, 15);
	cout << FGRN("X       X    X  X  X X  X   X  XXXX    XXXXXX    X       X");
	GotoXY(45, 16);
	cout << FGRN("XXXXXX  XXXXXX  X   XX  XXXXX  X   X  X      X   X    XXXX");
}

void quitboard()
{
	system("cls");
	GotoXY(45, 16);
	cout << FGRN("THANK YOU! WE HOPE YOU ENJOYED THE GAME!");
	Sleep(1000);
	system("cls");
}

void loadmenu()
{
	GotoXY(60, 16);
	cout << "L";
	Sleep(50);
	cout << "o";
	Sleep(50);
	cout << "a";
	Sleep(50);
	cout << "d";
	Sleep(50);
	cout << "i";
	Sleep(50);
	cout << "n";
	Sleep(50);
	cout << "g";
	for (int i = 0; i < 3; ++i)
	{
		GotoXY(67, 16);
		cout << '.';
		Sleep(200);
		cout << '.';
		Sleep(200);
		cout << '.';
		Sleep(300);
		GotoXY(67, 16);
		cout << "   ";
	}
	system("cls");
	Sleep(1000);
}
