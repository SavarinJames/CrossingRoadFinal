#include "header.h"

using namespace std;

CGAME::CGAME()
{
    shuffleLanes();
    level = 1;
    int maxObj = 3;
    int randNum;
    int beginX;
    bool leftSide;

    // for Trucks
    randNum = rand() % maxObj + 3;
    leftSide = rand() % 2;
    while (randNum--)
    {
        beginX = rand() % (CONSOLE_WIDTH - 1) + 1;
        CTRUCK *newTruck = new CTRUCK(beginX, ground + 5 * lanes[1], leftSide);
        trucks.push_back(newTruck);
    }

    // for Cars
    randNum = rand() % maxObj + 3;
    leftSide = rand() % 2;
    while (randNum--)
    {
        beginX = rand() % (CONSOLE_WIDTH - 1) + 1;
        CCAR *newCar = new CCAR(beginX, ground + 5 * lanes[2], leftSide);
        cars.push_back(newCar);
    }

    // for Dinos
    randNum = rand() % maxObj + 3;
    leftSide = rand() % 2;
    while (randNum--)
    {
        beginX = rand() % (CONSOLE_WIDTH - 1) + 1;
        CDINOSAUR *newDino = new CDINOSAUR(beginX, ground + 5 * lanes[3], leftSide);
        dinos.push_back(newDino);
    }

    // for Birds
    randNum = rand() % maxObj + 3;
    leftSide = rand() % 2;
    while (randNum--)
    {
        beginX = rand() % (CONSOLE_WIDTH - 1) + 1;
        CBIRD *newBird = new CBIRD(beginX, ground + 5 * lanes[4], leftSide);
        birds.push_back(newBird);
    }
}

void CGAME::startGame()
{
    system("cls");
    resetGame(1);
    drawMap(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    drawGame();
}

void CGAME::resetGame(int lev)
{
    deleteMovingObj();

    cls();

    shuffleLanes();
    level = lev;
    int maxObj = lev * 3;
    int randNum;
    int beginX;
    bool leftSide;

    // for Trucks
    randNum = rand() % maxObj + 3;
    leftSide = rand() % 2;
    while (randNum--)
    {
        beginX = rand() % (CONSOLE_WIDTH - 1) + 1;
        CTRUCK *newTruck = new CTRUCK(beginX, ground + 5 * lanes[1], leftSide);
        trucks.push_back(newTruck);
    }

    // for Cars
    randNum = rand() % maxObj + 3;
    leftSide = rand() % 2;
    while (randNum--)
    {
        beginX = rand() % (CONSOLE_WIDTH - 1) + 1;
        CCAR *newCar = new CCAR(beginX, ground + 5 * lanes[2], leftSide);
        cars.push_back(newCar);
    }

    // for Dinos
    randNum = rand() % maxObj + 3;
    leftSide = rand() % 2;
    while (randNum--)
    {
        beginX = rand() % (CONSOLE_WIDTH - 1) + 1;
        CDINOSAUR *newDino = new CDINOSAUR(beginX, ground + 5 * lanes[3], leftSide);
        dinos.push_back(newDino);
    }

    // for Birds
    randNum = rand() % maxObj + 3;
    leftSide = rand() % 2;
    while (randNum--)
    {
        beginX = rand() % (CONSOLE_WIDTH - 1) + 1;
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
    for (int i = 0; i < trucks.size(); i++)
        trucks[i]->move();
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

    for (int i = 0; i < trucks.size(); i++)
        trucks[i]->draw();
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

void ImpactEffect(int x, int y) {
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
    cout <<FRED( "OOPS!!$%");
    GotoXY(x + 3, y - 2);
    cout << FRED("  @~^");
}

/*
#include "car_move.h"

void CGAME::StartGame()
{
    while (!is_exit)
    {
        updateGame();
        DrawGame();
    }
}

void CGAME::DrawGame()
{
    for (int i = 0; i < L_NUM; ++i)
    {
        for (int j = 0; j < object.lane[i].size(); ++j)
        {
            object.lane[i][j]->Draw();
        }
    }

    Sleep(10);

    for (int i = 0; i < L_NUM; ++i)
    {
        for (int j = 0; j < object.lane[i].size(); ++j)
        {
            object.lane[i][j]->ReDraw();
        }
    }
}

void CGAME::updateGame()
{
    movingObjects *p;
    int current_location;

    for (int i = 0; i < L_NUM; ++i)
    {
        //Push random object to the a lane.
        if (rand() % 13 == 0)
        {
            //If the lane is empty, push without hesitation.
            if (!object.lane[i].empty())
            {
                current_location = object.lane[i].back()->getmX();
                if (!object.direction[i])
                    current_location = L_WIDTH - current_location;

                //Ensure the objects won't overlap each other.
                if (current_location < 5)
                    continue;
            }

            p = object.getMovingObject(i % 4 + 1, i);
            object.lane[i].push_back(p);
        }

        //Update objects' coordinate.
        for (int j = 0; j < object.lane[i].size(); ++j)
        {
            if (!object.lane[i][j]->move(object.direction[i]))
            {
                p = object.lane[i].front();
                object.lane[i].pop_front();
                delete p;
                --j;
            }
        }
    }
    DrawGame();
}
*/
