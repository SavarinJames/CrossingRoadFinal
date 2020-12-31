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