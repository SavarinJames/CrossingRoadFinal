#include "header.h"

CANIMAL::CANIMAL(int x, int y, bool goingLeft) : mX(x), mY(y), toLeft(goingLeft) {}

void CANIMAL::move()
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

bool CANIMAL::checkImpact(int cordX, int cordY)
{
	if (cordY != mY)
		return false;
	if (toLeft)
		return (cordX >= mX - 2 && cordX <= mX + 2);
	return (cordX <= mX && cordX >= mX - 4);
}

CBIRD::CBIRD(int x, int y, int goingLeft) : CANIMAL(x, y, goingLeft) {}

void CBIRD::draw()
{
	if (toLeft)
		GotoXY(mX, mY);
	else
		GotoXY(mX - 2, mY);
	cout << char(223) << char(220) << char(223);
}

CDINOSAUR::CDINOSAUR(int x, int y, int goingLeft) : CANIMAL(x, y, goingLeft) {}

void CDINOSAUR::draw()
{
	GotoXY(mX, mY - 1);
	cout << char(220);
	if (!toLeft)
	{
		GotoXY(mX - 2, mY);
		cout << char(220) << char(219) << char(223);
	}
	else
	{
		GotoXY(mX, mY);
		cout << char(223) << char(219) << char(220);
	}
}