#include "header.h"

CGAME game;
char DIRECTION;
bool IS_RUNNING;
bool IS_EXIT = true;
char MOVING;
int stoptime = 10;

void SubThread()
{
	while (IS_EXIT)
	{
		++stoptime;

		if (game.getLevel() > MAX_LEVEL)
		{
			IS_EXIT = false;
			winboard();
			mciSendString(TEXT("play wingame.mp3 "), NULL, 0, NULL);
			break;
		}
		Sleep(100);
		if (IS_RUNNING == true)
		{

			if (!game.getPeople().isDead())
			{
				game.updatePosVehicle();
				game.updatePosAnimal();
				if (MOVING != ' ')
				{
					game.updatePosPeople(MOVING);
					MOVING = ' ';
				}
				game.drawGame();
			}

			if (stoptime % 50 == 0)
				game.flipTruckLight();
			if (stoptime % 40 == 0)
				game.flipCarLight();

			if (game.getPeople().isImpact(game.getVehicle()) || game.getPeople().isImpact(game.getAnimal()))
			{
				int impCordX = game.getPeople().getX();
				int impCordY = game.getPeople().getY();
				GotoXY(impCordX, impCordY);
				bool VoA;
				if (game.getPeople().isImpact(game.getVehicle()))VoA = true;
				else if (game.getPeople().isImpact(game.getAnimal()))VoA = false;
				ImpactEffect(game.getPeople().getX(), game.getPeople().getY(),VoA);
				Sleep(1000);
				loseboard(game.getLevel());
				IS_EXIT = false;

				break;
			}

			if (game.getPeople().isFinished())
			{
				if (game.getLevel() < MAX_LEVEL)
				{
					game.resetGame(game.getLevel() + 1);
					mciSendString(TEXT("play passlevel.mp3 "), NULL, 0, NULL);
					stoptime = 10;
					displayLevel(game.getLevel());
					drawMap(CONSOLE_WIDTH, CONSOLE_HEIGHT, game.getLevel());
				}
				else game.setLevel(game.getLevel() + 1);
			}

			//Sleep(100 / cg->getSpeed());
		}
	}
}

int main()
{
	hidecursor();
	setConsoleSize();
	FixConsoleWindow();
	int levelt;
	loadmenu();
	char t = '1';
	//string m = "open \"*.mp3\" type mpegvideo alias mp3";
	//mciSendString(_T("play Music.mp3 repeat"), NULL, 0, NULL);
	
	while (t != '4')
	{
		menu();
		t = _getch();
		//game = new CGAME();
		IS_EXIT = true;
		IS_RUNNING = true;
		MOVING = ' '; stoptime = 10;
		if (t == '1' || t == '2') {
			if (t == '2') {
				ifstream fin; int numberOfSave = 0; SaveFile* File[100];
				fin.open("SaveFile.txt");

				int level; string name;
				GotoXY(17, 15);
				if (fin.peek() == ifstream::traits_type::eof())
					cout << "There is no save file!!";
				else {
					cout << char(254) <<" Here are saved files: ";
					int line = 18;
					while (!(fin.peek() == ifstream::traits_type::eof())) {
						getline(fin, name);
						fin >> level;
						fin.ignore(100, '\n');
						File[numberOfSave] = new SaveFile(level, name);
						GotoXY(23, 17);cout << FYEL("NAME");GotoXY(31, 17);cout << FGRN("LEVEL ");
						GotoXY(19, line);
						cout << numberOfSave + 1 << ".  " << File[numberOfSave]->getName();GotoXY(33,line);cout << File[numberOfSave]->getLevel();
						numberOfSave += 1; line += 1;
					}

					fin.close();

					char type; type = _getch();
					if (type != 27) {
						int a = type - '0';
						if (a <= numberOfSave && a > 0) {
							levelt = File[a - 1]->getLevel();
							//game.setLevel(level);
						}
					}
					else continue;
				}
			}
			else if (t == '1') {
				levelt = 1;
			}

			int temp = 0;
			setConsoleSize();
			FixConsoleWindow();
			displayLevel(levelt);
			game.startGame(levelt);
			thread t1(SubThread);
			while (IS_EXIT)
			{
				hidecursor();
				temp = toupper(_getwch());
				if (!game.getPeople().isDead())
				{
					if (temp == 27)
					{
						//game.exitGame(t1.native_handle());
						IS_EXIT = false;
					}
					else if (temp == 'P')
					{
						if (IS_RUNNING)
						{
							IS_RUNNING = false;
						}
						else
						{
							IS_RUNNING = true;
						}
					}
					else if (temp == 'K') {
						if (IS_RUNNING) {}
						else game.saveGame();
					}
					else if (temp == 'L') {

						if (IS_RUNNING) {}
						
						else if(!IS_EXIT)game.loadGame();
					}
					else
					{
						if (IS_RUNNING)
							MOVING = temp;
					}
				}
				else
				{
					if (temp == 'Y')
						game.startGame(levelt);
					else
					{
						//game.exitGame(t1.native_handle());
						return 0;
					}
				}
			}
			t1.join();
		}
		else if (t == '3')
		{
			system("cls");
			GotoXY(50, 16);
			cout << "   Input again.";
			Sleep(2000);
		}
	}
	quitboard();
	return 0;
}
