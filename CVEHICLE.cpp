#include "header.h"

CVEHICLE::CVEHICLE(int x, int y, bool goingLeft) : mX(x), mY(y), toLeft(goingLeft) {}

void CVEHICLE::move()
{
	if (toLeft)
	{
		mX--;
		if (mX <= 0)
			mX = CONSOLE_WIDTH - 3;
	}
	else
	{
		mX++;
		if (mX >= CONSOLE_WIDTH)
			mX = 3;
	}
}

bool CVEHICLE::checkImpact(int cordX, int cordY)
{
	if (cordY != mY)
		return false;
	if (toLeft)
		return (cordX >= mX - 2 && cordX <= mX + 2);
	return (cordX <= mX && cordX >= mX - 4);
}

CCAR::CCAR(int x, int y, bool goingLeft) : CVEHICLE(x, y, goingLeft) {}

void CCAR::draw()
{
	if (toLeft)
		GotoXY(mX, mY);
	else
		GotoXY(mX - 2, mY);
	cout << char(220) << char(219) << char(220);
}

CTRUCK::CTRUCK(int x, int y, bool goingLeft) : CVEHICLE(x, y, goingLeft){};

void CTRUCK::draw()
{
	GotoXY(mX, mY);
	cout << char(220);
	if (!toLeft)
		GotoXY(mX - 2, mY);
	cout << char(219) << char(219);
}