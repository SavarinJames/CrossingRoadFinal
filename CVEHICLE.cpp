#include "header.h"

using namespace std;

CVEHICLE::CVEHICLE(int x, int y, bool goingLeft) : mX(x), mY(y), toLeft(goingLeft) {}

void CVEHICLE::move()
{
	if (toLeft)
		mX--;
	else
		mX++;
	if (mX <= 0 || mX >= CONSOLE_WIDTH)
		mX = (mX + CONSOLE_WIDTH - 2) % (CONSOLE_WIDTH - 1) + 1;
}

CCAR::CCAR(int x, int y, bool goingLeft) : CVEHICLE(x, y, goingLeft) {}

void CCAR::draw()
{
	GotoXY(mX, mY);
	cout << shape;
}

CTRUCK::CTRUCK(int x, int y, bool goingLeft) : CVEHICLE(x, y, goingLeft) {};

void CTRUCK::draw()
{
	GotoXY(mX, mY);
	cout << shape;
}