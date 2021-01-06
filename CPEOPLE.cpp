#include "header.h"

CPEOPLE::CPEOPLE() : mX(CONSOLE_WIDTH / 2), mY(CONSOLE_HEIGHT - 2), mState(true) {}

void CPEOPLE::revive()
{
	mX = CONSOLE_WIDTH / 2;
	mY = CONSOLE_HEIGHT - 2;
	mState = true;
}

void CPEOPLE::draw()
{
	GotoXY(mX, mY - 2);
	cout << " 0";
	GotoXY(mX, mY - 1);
	cout << "/|" << char(92);
	GotoXY(mX, mY - 0);
	cout << "/ " << char(92);
}

void CPEOPLE::Up()
{
	if (mY - 5 <= 0)
		return;
	mY -= 5;
}

void CPEOPLE::Down()
{
	if (mY + 5 >= CONSOLE_HEIGHT - 1)
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
	if (mX + speed >= CONSOLE_WIDTH - 2)
		return;
	mX += speed;
}

bool CPEOPLE::isImpact(const vector<CVEHICLE *> &vehicles)
{
	for (int i = 0; i < vehicles.size(); i++)
		if (vehicles[i]->checkImpact(mX, mY))
		{
			mState = false;
			return true;
		}
	return false;
}

bool CPEOPLE::isImpact(const vector<CANIMAL *> &animals)
{
	for (int i = 0; i < animals.size(); i++)
		if (animals[i]->checkImpact(mX, mY))
		{
			mState = false;
			return true;
		}
	return false;
}

bool CPEOPLE::isDead()
{
	return !mState;
}

bool CPEOPLE::isFinished()
{
	return (mY == 4);
}
