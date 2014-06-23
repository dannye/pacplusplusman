#include "includes.h"

using namespace std;

char level[LEVELHEIGHT][LEVELWIDTH];
int oneuptimer = ONEUPMAX;
int oneupcolor = WHITE;
int pellettimer = PELLETMAX;
int pelletcolor = WHITE;
int ghostmode = MODEMAX;

pacman player;
ghost ghosts[4];
pellet pellets[4];
