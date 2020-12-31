#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;

const int CONSOLE_WIDTH = 150;
const int CONSOLE_HEIGHT = 31;
const int ground = 4;

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

void draw(int x, int y)
{
    GotoXY(x, y);
    cout << char(219);
    return;
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

// class MovingObj
// {
// protected:
//     int mX, mY; // top left cordinate;
//     int height, width;

// public:
//     MovingObj() : mX(0), mY(0), height(0), width(0) {}
//     MovingObj(int cordX, int cordY, int hi, int wi) : mX(cordX), mY(cordY), height(hi), width(wi) {}
//     virtual void draw() = 0;
//     virtual bool impact(int cordX, int cordY) = 0;
// };

class CVEHICLE
{
protected:
    int mX, mY;
    bool toLeft;

public:
    CVEHICLE(int x, int y, bool goingLeft) : mX(x), mY(y), toLeft(goingLeft) {}
    void move()
    {
        if (toLeft)
            mX--;
        else
            mX++;
        if (mX <= 0 || mX >= CONSOLE_WIDTH)
            mX = (mX + CONSOLE_WIDTH - 2) % (CONSOLE_WIDTH - 1) + 1;
    }
    virtual void draw() = 0;
    int getX() { return mX; }
    int getY() { return mY; }
};

class CCAR : public CVEHICLE
{
public:
    const string shape = "C";
    CCAR(int x, int y, bool goingLeft) : CVEHICLE(x, y, goingLeft){};
    void draw()
    {
        GotoXY(mX, mY);
        cout << shape;
    }
};

class CTRUCK : public CVEHICLE
{
public:
    const string shape = "T";
    CTRUCK(int x, int y, bool goingLeft) : CVEHICLE(x, y, goingLeft){};
    void draw()
    {
        GotoXY(mX, mY);
        cout << shape;
    }
};

class CANIMAL
{
protected:
    int mX, mY;
    bool toLeft;

public:
    CANIMAL(int x, int y, bool goingLeft) : mX(x), mY(y), toLeft(goingLeft) {}
    void move()
    {
        if (toLeft)
            mX--;
        else
            mX++;
        if (mX <= 0 || mX >= CONSOLE_WIDTH)
            mX = (mX + CONSOLE_WIDTH - 2) % (CONSOLE_WIDTH - 1) + 1;
    }
    virtual void draw() = 0;
    int getX() { return mX; }
    int getY() { return mY; }
};

class CBIRD : public CANIMAL
{
public:
    const string shape = "B";
    CBIRD(int x, int y, int goingLeft) : CANIMAL(x, y, goingLeft) {}
    void draw()
    {
        GotoXY(mX, mY);
        cout << shape;
    }
};

class CDINOSAUR : public CANIMAL
{
public:
    const string shape = "D";
    CDINOSAUR(int x, int y, int goingLeft) : CANIMAL(x, y, goingLeft) {}
    void draw()
    {
        GotoXY(mX, mY);
        cout << shape;
    }
};

class CPEOPLE
{
private:
    int mX, mY;
    bool mState;

public:
    const string shape = "Y";
    CPEOPLE() : mX(CONSOLE_WIDTH / 2), mY(CONSOLE_HEIGHT - 2), mState(true) {}
    void Up();
    void Left(int speed);
    void Right(int speed);
    void Down();
    bool isImpact(const vector<CVEHICLE *> &vehicles, int &impCordX, int &impCordY);
    bool isImpact(const vector<CANIMAL *> &animals, int &impCordX, int &impCordY);
    bool isFinished();
    bool isDead();
    void draw()
    {
        GotoXY(mX, mY);
        cout << shape;
    }
};

void CPEOPLE::Up()
{
    if (mY - 5 <= 0)
        return;
    mY -= 5;
}

void CPEOPLE::Down()
{
    if (mY + 5 <= CONSOLE_HEIGHT - 1)
        return;
    mY += 5;
}

void CPEOPLE::Left(int speed)
{
    if (mX - speed <= 0)
        return;
    mX -= speed;
}

void CPEOPLE::Right(int speed)
{
    if (mX + speed >= CONSOLE_WIDTH - 1)
        return;
    mX += speed;
}

bool CPEOPLE::isFinished()
{
    return (mY == 4);
}

bool CPEOPLE::isImpact(const vector<CVEHICLE *> &vehicles, int &impCordX, int &impCordY)
{
    for (int i = 0; i < vehicles.size(); i++)
        if (vehicles[i]->getX() == mX && vehicles[i]->getY() == mY)
        {
            impCordX = mX;
            impCordY = mY;
            mState = false;
            return true;
        }
    return false;
}

bool CPEOPLE::isImpact(const vector<CANIMAL *> &animals, int &impCordX, int &impCordY)
{
    for (int i = 0; i < animals.size(); i++)
        if (animals[i]->getX() == mX && animals[i]->getY() == mY)
        {
            impCordX = mX;
            impCordY = mY;
            mState = false;
            return true;
        }
    return false;
}

bool CPEOPLE::isDead()
{
    return !mState;
}

class CGAME
{
private:
    int level;
    int lanes[5] = {0, 1, 2, 3, 4};
    vector<CTRUCK *> trucks;
    vector<CCAR *> cars;
    vector<CDINOSAUR *> dinos;
    vector<CBIRD *> birds;
    CPEOPLE human;

public:
    void shuffleLanes();
    CGAME(int lev);
    ~CGAME();
    void drawGame();
    CPEOPLE getPeople();
    vector<CVEHICLE *> getVehicle();
    vector<CANIMAL *> getAnimal();
    void resetGame(int lev);
    void exitGame(HANDLE);
    void startGame();
    void loadGame(ifstream);
    void saveGame(ofstream);
    void pauseGame(HANDLE);
    void resumeGame(HANDLE);
    void updatePosPeople(int direction);
    void updatePosVehicle();
    void updatePosAnimal();
    void deleteMovingObj();
};

CGAME::CGAME(int lev)
{
    resetGame(lev);
    // trucks = new CTRUCK(1, ground + 5 * lanes[1], true);
    // cars = new CCAR(CONSOLE_WIDTH - 1, ground + 5 * lanes[2], false);
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

void CGAME::resetGame(int lev)
{
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

CGAME::~CGAME()
{
    deleteMovingObj();
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

void CGAME::updatePosPeople(int direction)
{
    switch (direction)
    {
    case (87):
        human.Up();
        break;
    case (65):
        human.Left(2);
        break;
    case (83):
        human.Down();
        break;
    case (68):
        human.Right(2);
        break;
    default:
        break;
    }
}

void CGAME::updatePosAnimal()
{
    for (int i = 0; i < birds.size(); i++)
        birds[i]->move();
    for (int i = 0; i < dinos.size(); i++)
        dinos[i]->move();
}

void CGAME::drawGame()
{
    cls();

    for (int i = 0; i < trucks.size(); i++)
        trucks[i]->draw();
    for (int i = 0; i < cars.size(); i++)
        cars[i]->draw();

    for (int i = 0; i < dinos.size(); i++)
        dinos[i]->move();
    for (int i = 0; i < birds.size(); i++)
        birds[i]->draw();

    human.draw();

    Sleep(100 / (5 * level)); // increases the speed of the objects
}

#endif