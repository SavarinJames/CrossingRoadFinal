#include "header.h"

using namespace std;

CLIGHT::CLIGHT() :mX(0), mY(0), red(false) {}

void CLIGHT::lightSwitch() { red = !red; }

void CLIGHT::setCord(int cordX, int cordY)
{
	mX = cordX;
	mY = cordY;
	red = false;
}

void CLIGHT::draw()
{
	GotoXY(mX, mY);

	if (red)
	{
		SetColor(4);
		cout << char(220);
		GotoXY(mX, mY + 1);
		SetColor(8);
		cout << char(223);
	}
	else
	{
		SetColor(8);
		cout << char(220);
		GotoXY(mX, mY + 1);
		SetColor(10);
		cout << char(223);
	}

	SetColor(15);
}