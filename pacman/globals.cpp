#include "includes.h"

using namespace std;

char level[LEVELHEIGHT][LEVELWIDTH];
int oneuptimer = ONEUPMAX;
int oneupcolor = WHITE;
int pellettimer = PELLETMAX;
int pelletcolor = WHITE;
int ghostmode = MODEMAX;

pacman player;
ghost blinky;
ghost pinky;
ghost inky;
ghost clyde;
pellet one;
pellet two;
pellet three;
pellet four;
