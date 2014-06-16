#include "includes.h"

using namespace std;

void pellet::print()
{
    SetCursorPosition(y, x);
    cout << level[y][x];
}
