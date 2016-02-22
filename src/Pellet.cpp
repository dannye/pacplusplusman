#include <iostream>

#include "Game.h"
#include "Pellet.h"
#include "SetConsoleAttributes.h"

using namespace std;

Pellet::Pellet(Game *const g)
: game(g) {}

void Pellet::Print() {
    SetCursorPosition(y, x);
    cout << game->GetLevel(y, x);
}
