#include "header.h"

using namespace std;

CGAME game;
char DIRECTION;
bool IS_RUNNING;
bool IS_EXIT = true;
char MOVING;
int stoptime = 10;
// void exitGame(thread *t)
// {
//     cls();
//     IS_RUNNING = false;
//     t->join();
// }

// void threadFunc1()
// {
//     while (IS_RUNNING)
//     {
//         if(!game.getPeople().isDead())
//             game.updatePosPeople(DIRECTION);
//         DIRECTION = ' ';
//         game.updatePosVehicle();
//         game.updatePosAnimal();
//         game.drawGame();

//         if(game.getPeople().isImpact(game.getVehicle()) || game.getPeople().isImpact(game.getAnimal()))
//             {
//                 int impCordX = game.getPeople().getX();
//                 int impCordY = game.getPeople().getY();
//                 GotoXY(impCordX, impCordY);
// 				cout << char(178);
//                 IS_RUNNING = false;
//             }
//         if(game.getPeople().isFinished())
//                 game.resetGame(game.getLevel() + 1);
//         Sleep(100);
//     }
// }

/*
int main()
{
    system("cls");
    srand(time(NULL));
    setConsoleSize();
    FixConsoleWindow();
    hidecursor();

    IS_RUNNING = true;

    game.startGame();
    /*
    while (IS_RUNNING)
    {
        DIRECTION = toupper(_getch());
        if(DIRECTION == 27)
            return 0;
        if(!game.getPeople().isDead())
            game.updatePosPeople(DIRECTION);
        DIRECTION = ' ';
        game.updatePosVehicle();
        game.updatePosAnimal();
        game.drawGame();

        if(game.getPeople().isImpact(game.getVehicle()) || game.getPeople().isImpact(game.getAnimal()))
            {
                int impCordX = game.getPeople().getX();
                int impCordY = game.getPeople().getY();
                GotoXY(impCordX, impCordY);
				cout << char(178);
                IS_RUNNING = false;
            }
        if(game.getPeople().isFinished())
                game.resetGame(game.getLevel() + 1);
        Sleep(100);
    }
    
    // thread t1(threadFunc1);
    // while (1)
    // {
    //     int temp = toupper(getch());
    //     if (!game.getPeople().isDead())
    //         switch (temp)
    //         {
    //         case 27:
    //             game.exitGame(t1.native_handle());
    //             return 0;
    //         case 'P':
    //             game.pauseGame(t1.native_handle());
    //             break;
    //         default:
    //             game.resumeGame((HANDLE)t1.native_handle());
    //             DIRECTION = temp;
    //             break;
    //         }
    //     else
    //     {
    //         if(temp == 'Y')
    //             game.startGame();
    //         else 
    //         {
    //             game.exitGame(t1.native_handle());
    //             return 0;
    //         }
    //     }
    // }
}
*/
void SubThread() {
	while (IS_EXIT) {
		//++stoptime;
		
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
			Sleep(2000);
			//cout << char(178);
			//game.resetGame();
			IS_EXIT = false;
			
			break;
		}

		//Sleep(100 / cg->getSpeed());
	}
	
}


int main() {

	
	char t = '1';
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
			int temp=0;
			setConsoleSize();
			FixConsoleWindow();
			
			game.startGame();
			thread t1(SubThread);
			while (IS_EXIT) {
				hidecursor();
				temp=toupper(_getwch());
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


