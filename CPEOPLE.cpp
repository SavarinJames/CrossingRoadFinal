#include "header.h"

using namespace std;

CPEOPLE::CPEOPLE() : mX(CONSOLE_WIDTH / 2), mY(CONSOLE_HEIGHT - 2), mState(true) {}

void CPEOPLE::revive()
{
    mX = CONSOLE_WIDTH / 2;
    mY = CONSOLE_HEIGHT - 2;
    mState = true;
}

void CPEOPLE::draw()
{
    GotoXY(mX, mY);
    cout << shape;
}

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

bool CPEOPLE::isImpact(const vector<CVEHICLE *> &vehicles)
{
    for (int i = 0; i < vehicles.size(); i++)
        if (vehicles[i]->getX() == mX && vehicles[i]->getY() == mY)
        {
            mState = false;
            return true;
        }
    return false;
}

bool CPEOPLE::isImpact(const vector<CANIMAL *> &animals)
{
    for (int i = 0; i < animals.size(); i++)
        if (animals[i]->getX() == mX && animals[i]->getY() == mY)
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