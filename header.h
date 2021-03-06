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
#include <map>
#include <sstream>
#pragma comment(lib, "Winmm.lib")

#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

using namespace std;

const int MAX_LEVEL = 5;
const int CONSOLE_WIDTH = 100;
const int CONSOLE_HEIGHT = 31;
const int CONSOLE_INTWIDTH = 130;
const int ground = 4;

void FixConsoleWindow();
void GotoXY(int x, int y);
void setConsoleSize();
void cls();
void hidecursor();
void SetColor(int ForgC);

void drawMap(int width, int height, int level);

void menu();
void ImpactEffect(int x, int y,bool VoA);
void displayLevel(int level);

void loadmenu();
void loseboard(int level);
void winboard();
void quitboard();

class CVEHICLE
{
protected:
	int mX, mY;
	bool toLeft;

public:
	CVEHICLE(int x, int y, bool goingLeft);

	void move();
	virtual void draw() = 0;

	bool checkImpact(int cordX, int cordY);

	int getX() { return mX; }
	int getY() { return mY; }
};

class CCAR : public CVEHICLE
{
public:
	const string shape = "C";
	CCAR(int x, int y, bool goingLeft);
	void draw();
};

class CTRUCK : public CVEHICLE
{
public:
	const string shape = "T";
	CTRUCK(int x, int y, bool goingLeft);
	void draw();
};

class CANIMAL
{
protected:
	int mX, mY;
	bool toLeft;

public:
	CANIMAL(int x, int y, bool goingLeft);

	void move();
	virtual void draw() = 0;

	bool checkImpact(int cordX, int cordY);

	int getX() { return mX; }
	int getY() { return mY; }
};

class CBIRD : public CANIMAL
{
public:
	const string shape = "B";
	CBIRD(int x, int y, int goingLeft);
	void draw();
};

class CDINOSAUR : public CANIMAL
{
public:
	const string shape = "D";
	CDINOSAUR(int x, int y, int goingLeft);
	void draw();
};

class SaveFile {
private:
	string name;
	int level;
public:
	int getLevel();
	string getName();
	SaveFile(int, string);
};

class CPEOPLE
{
private:
	int mX, mY;
	bool mState;

public:
	const string shape = "???";
	CPEOPLE();

	void revive();
	void Up();
	void Left(int speed);
	void Right(int speed);
	void Down();

	bool isImpact(const vector<CVEHICLE*>& vehicles);
	bool isImpact(const vector<CANIMAL*>& animals);
	bool isFinished();
	bool isDead();

	void draw();

	int getX() { return mX; }
	int getY() { return mY; }
};

class CLIGHT
{
private:
	int mX, mY;
	bool red;

public:
	CLIGHT();

	void setCord(int cordX, int cordY);
	void lightSwitch();
	void draw();

	bool canGo() { return !red; }
};

class CGAME
{
private:

	int level, numOfFiles;
	int lanes[5] = { 0, 1, 2, 3, 4 };
	vector<CTRUCK*> trucks;
	vector<CCAR*> cars;
	vector<CDINOSAUR*> dinos;
	vector<CBIRD*> birds;
	SaveFile* File[10];
	CPEOPLE human;
	CLIGHT truckLight, carLight;

public:
	CGAME();
	~CGAME();

	CPEOPLE getPeople();
	vector<CVEHICLE*> getVehicle();
	vector<CANIMAL*> getAnimal();

	void shuffleLanes();

	void flipTruckLight();
	void flipCarLight();

	void drawGame();
	//void updateLevel();

	void resetGame(int lev);
	void startGame(int level1);
	void loadGame();
	void saveGame();
						 
	void updatePosPeople(int direction);
	void updatePosVehicle();
	void updatePosAnimal();

	void deleteMovingObj();
	int getLevel() { return level; }
	int setLevel(int lev);
	void Clean();
};

#endif