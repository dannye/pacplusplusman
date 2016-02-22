#include "Game.h"

int main() {
    Game* game = new Game();
    game->Go();
    delete game;
    return 0;
}
