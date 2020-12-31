#include "header.h"

using namespace std;

CGAME game;
char DIRECTION;
bool IS_RUNNING;

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

int main()
{
    system("cls");
    srand(time(NULL));
    setConsoleSize();
    FixConsoleWindow();
    hidecursor();

    IS_RUNNING = true;

    game.startGame();

    while (IS_RUNNING)
    {
        DIRECTION = toupper(getch());
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