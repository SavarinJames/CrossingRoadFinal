#include "header.h"

using namespace std;

CANIMAL::CANIMAL(int x, int y, bool goingLeft) : mX(x), mY(y), toLeft(goingLeft) {}

void CANIMAL::move()
{
	if (toLeft)
		mX--;
	else
		mX++;
	if (mX <= 0 || mX >= CONSOLE_WIDTH)
		mX = (mX + CONSOLE_WIDTH - 2) % (CONSOLE_WIDTH - 1) + 1;
}

CBIRD::CBIRD(int x, int y, int goingLeft) : CANIMAL(x, y, goingLeft) {}

void CBIRD::draw()
{
	GotoXY(mX, mY);
	cout << shape;
}

CDINOSAUR::CDINOSAUR(int x, int y, int goingLeft) : CANIMAL(x, y, goingLeft) {}

void CDINOSAUR::draw()
{
	GotoXY(mX, mY);
	cout << shape;
}

/*
#include "car_move.h"

void Objects::setLanesDirection()
{
	for (int i = 0; i < L_NUM; ++i)
		direction[i] = rand() % 2;
}

movingObjects *Objects::getMovingObject(const int type, const int n_lane)
{
	switch (type)
	{
	case 1: //car
		return new CCAR((direction[n_lane] ? 0 : L_WIDTH), n_lane * L_HEIGHT + 1);
	case 2: //truck
		return new CTRUCK((direction[n_lane] ? 0 : L_WIDTH), n_lane * L_HEIGHT + 1);
	case 3: //bird
		return new CBIRD((direction[n_lane] ? 0 : L_WIDTH), n_lane * L_HEIGHT + 1);
	case 4: //dinosaurs
		return new CDINO((direction[n_lane] ? 0 : L_WIDTH), n_lane * L_HEIGHT + 1);
	default:
		cout << "Wrong type!\n";
		return nullptr;
	}
}

bool movingObjects::move(const bool &direction)
{
	if (direction)
		++this->mX;
	else
		--this->mX;

	if (direction && this->mX >= L_WIDTH)
		return false;
	if (!direction && this->mX <= 0)
		return false;

	return true;
}

void CCAR::Draw()
{
	if (mX >= 0 && mY >= 0)
		GotoXY(mX, mY);
	else
		GotoXY(0, mY);

	if (mX > 3 && mX < L_WIDTH - 3)
	{
		cout << char(220) << char(219) << char(219) << char(220) << '\0';
		return;
	}
	if (mX == 1 || mX == L_WIDTH - 1)
	{
		cout << char(220) << '\0';
		return;
	}
	if (mX == 2)
	{
		cout << char(219) << char(220) << '\0';
		return;
	}
	if (mX == 3)
	{
		cout << char(219) << char(219) << char(220) << '\0';
		return;
	}
	if (mX == L_WIDTH - 3)
	{
		cout << char(220) << char(219) << char(219) << '\0';
		return;
	}
	if (mX == L_WIDTH - 2)
	{
		cout << char(220) << char(219) << '\0';
		return;
	}
}

void CCAR::ReDraw()
{
	if (mX >= 0 && mY >= 0)
		GotoXY(mX, mY);
	else
		GotoXY(0, mY);

	if (mX > 3 && mX < L_WIDTH - 3)
	{
		cout << "    " << '\0';
		return;
	}

	if (mX == 1 || mX == L_WIDTH - 1)
	{
		cout << " ";
		return;
	}
	if (mX == 2 || mX == L_WIDTH - 2)
	{
		cout << "  ";
		return;
	}
	if (mX == 3 || mX == L_WIDTH - 3)
	{
		cout << "   ";
		return;
	}
}

void CTRUCK::Draw()
{
	if (mX >= 0 && mY >= 0)
		GotoXY(mX, mY);
	else
		GotoXY(0, mY);

	if (mX > 2 && mX < L_WIDTH - 2)
	{
		cout << char(222) << char(219) << char(220) << '\0';
		return;
	}

	if (mX == 1)
	{
		cout << char(220) << '\0';
		return;
	}

	if (mX == 2)
	{
		cout << char(219) << char(220) << '\0';
		return;
	}

	if (mX == L_WIDTH - 1)
	{
		cout << char(222) << '\0';
		return;
	}

	if (mX == L_WIDTH - 2)
	{
		cout << char(222) << char(219) << '\0';
		return;
	}
}

void CTRUCK::ReDraw()
{
	if (mX >= 0 && mY >= 0)
		GotoXY(mX, mY);
	else
		GotoXY(0, mY);

	if (mX > 2 && mX < L_WIDTH - 2)
	{
		cout << "   ";
		return;
	}

	if (mX == 1)
	{
		cout << " ";
		return;
	}

	if (mX == 2)
	{
		cout << "  ";
		return;
	}

	if (mX == L_WIDTH - 1)
	{
		cout << " ";
		return;
	}

	if (mX == L_WIDTH - 2)
	{
		cout << "  ";
		return;
	}
}

void CBIRD::Draw()
{
	if (mX >= 0 && mY >= 0)
		GotoXY(mX, mY - 1);
	else
		GotoXY(0, mY - 1);

	if (mX > 2 && mX < L_WIDTH - 2)
	{
		cout << char(223) << char(220) << char(223) << '\0'; //▀▄▀
		return;
	}

	if (mX == 1)
	{
		cout << char(223) << '\0';
		return;
	}

	if (mX == 2)
	{
		cout << char(220) << char(223) << '\0';
		return;
	}

	if (mX == L_WIDTH - 1)
	{
		cout << char(223) << '\0';
		return;
	}

	if (mX == L_WIDTH - 2)
	{
		cout << char(223) << char(220) << '\0';
		return;
	}
}

void CBIRD::ReDraw()
{
	if (mX >= 0 && mY >= 0)
		GotoXY(mX, mY - 1);
	else
		GotoXY(0, mY - 1);

	if (mX > 2 && mX < L_WIDTH - 2)
	{
		cout << "   ";
		return;
	}

	if (mX == 1)
	{
		cout << " ";
		return;
	}

	if (mX == 2)
	{
		cout << "  ";
		return;
	}

	if (mX == L_WIDTH - 1)
	{
		cout << " ";
		return;
	}

	if (mX == L_WIDTH - 2)
	{
		cout << "  ";
		return;
	}
}

void CDINO::Draw()
{
	if (mX >= 0 && mY >= 0)
		GotoXY(mX, mY - 1);
	else
		GotoXY(0, mY - 1);

	if (mX > 2 && mX < L_WIDTH - 2)
	{
		cout << char(220) << "\0";
		GotoXY(mX, mY);
		cout << char(223) << char(219) << char(220) << '\0';
		return;
	}

	if (mX == 1)
	{
		GotoXY(mX, mY);
		cout << char(220) << '\0';
		return;
	}

	if (mX == 2)
	{
		GotoXY(mX, mY);
		cout << char(219) << char(220) << '\0';
		return;
	}

	if (mX == L_WIDTH - 1)
	{
		cout << char(220) << "\0";
		GotoXY(mX, mY);
		cout << char(223) << '\0';
		return;
	}

	if (mX == L_WIDTH - 2)
	{
		cout << char(220) << "\0";
		GotoXY(mX, mY);
		cout << char(223) << char(219) << '\0';
		return;
	}
}

void CDINO::ReDraw()
{
	if (mX >= 0 && mY >= 0)
		GotoXY(mX, mY - 1);
	else
		GotoXY(0, mY - 1);

	if (mX > 2 && mX < L_WIDTH - 2)
	{
		cout << " ";
		GotoXY(mX, mY);
		cout << "   ";
		return;
	}

	if (mX == 1)
	{
		GotoXY(mX, mY);
		cout << " ";
		return;
	}

	if (mX == 2)
	{
		GotoXY(mX, mY);
		cout << "  ";
		return;
	}

	if (mX == L_WIDTH - 1)
	{
		cout << " ";
		GotoXY(mX, mY);
		cout << " ";
		return;
	}

	if (mX == L_WIDTH - 2)
	{
		cout << " ";
		GotoXY(mX, mY);
		cout << "  ";
		return;
	}
}

*/