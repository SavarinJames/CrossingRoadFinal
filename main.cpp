#include "header.h"

using namespace std;

CGAME game;
char DIRECTION;
bool IS_RUNNING;
bool IS_EXIT = true;
char MOVING;
int stoptime = 10;


void SubThread() {
	while (IS_EXIT) {
		++stoptime;

		Sleep(100);
		//if (IS_RUNNING==false) ;
		if (!game.getPeople().isDead())
		{
			game.updatePosVehicle();
			game.updatePosAnimal();
			if (MOVING != ' ') {
				game.updatePosPeople(MOVING);
				MOVING = ' ';
			}
			game.drawGame();
		}

		if (stoptime % 100 == 0) game.flipTruckLight();
		if (stoptime % 70 == 0) game.flipCarLight();

		/*
		if (game.IsFinish()) {
			game.ScoreBoard(true);
			IS_EXIT = false;
			break;
		}
		*/

		/*
		MOVING = ' ';
		if (stoptime % 20 > 10) {
			cg->DrawLight(true);
			cg->Update();
		}
		else {
			cg->DrawLight(false);
		}*/
		if (game.getPeople().isImpact(game.getVehicle()) || game.getPeople().isImpact(game.getAnimal()))
		{
			int impCordX = game.getPeople().getX();
			int impCordY = game.getPeople().getY();
			GotoXY(impCordX, impCordY);
			ImpactEffect(game.getPeople().getX(), game.getPeople().getY());
			Sleep(1000);
			//cout << char(178);
			//game.resetGame();
			IS_EXIT = false;

			break;
		}

		if (game.getPeople().isFinished())
		{
			game.resetGame(game.getLevel() + 1);
			stoptime = 10;
		}

		//Sleep(100 / cg->getSpeed());
	}

}


int main() {

	char t = '1';
	//string m = "open \"*.mp3\" type mpegvideo alias mp3";
	//mciSendString(_T("play Music.mp3 repeat"), NULL, 0, NULL);
	while (t != '4')
	{
		hidecursor();
		setConsoleSize();
		FixConsoleWindow();
		menu();
		t = _getch();
		//game = new CGAME();
		IS_EXIT = true;
		IS_RUNNING = true;
		MOVING = ' '; stoptime = 10;
		if (t == '1' || t == '2') {
			if (t == '2') {
				// loadgame.
			}
			int temp = 0;
			setConsoleSize();
			FixConsoleWindow();

			game.startGame();
			thread t1(SubThread);
			while (IS_EXIT) {
				hidecursor();
				temp = toupper(_getwch());
				if (!game.getPeople().isDead()) {
					if (temp == 27) {
						//game.exitGame(t1.native_handle());
						IS_EXIT = false;
					}
					else if (temp == 'P') {
						if (IS_RUNNING) {
							IS_RUNNING = false;
							//game.pauseGame(t1.native_handle());
						}
						else {
							IS_RUNNING = true;
							//game.resumeGame(t1.native_handle());
						}
					}
					else if (temp == 'K') {
						if (IS_RUNNING) {}
						//else game.saveGame();
					}
					else if (temp == 'L') {
						if (IS_RUNNING) {}
						//else game.loadGame();
					}
					else {
						if (IS_RUNNING) MOVING = temp;
					}
				}
				else {
					if (temp == 'Y') game.startGame();
					else {
						//game.exitGame(t1.native_handle());
						return 0;
					}
				}
			}
			t1.join();
		}
		else if (t == '3') {
			GotoXY(50, 16);  cout << "   Input again.";
			Sleep(2000);
		}
	}
	return 0;
}


