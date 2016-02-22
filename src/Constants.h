#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Windows.h>

// level properties
const int LEVEL_HEIGHT = 31;
const int LEVEL_WIDTH  = 28;
const char NO_COLLISION_TILES[3] = {' ','o','\xfa'};
const int GATE_X = 13;
const int GATE_Y = 12;

// directions and icons
const char ALL_DIRS[4]     = {'w','a','s','d'};
const char ICONS[4]        = {'v','>','^','<'};
const char GHOST_ICON      = 'M';
const char DEAD_GHOST_ICON = '"';

// colors
const int WHITE     = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int RED       = FOREGROUND_RED   | FOREGROUND_INTENSITY;
const int BLUE      = FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
const int DARK_BLUE = FOREGROUND_BLUE;
const int CYAN      = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
const int MAGENTA   = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
const int YELLOW    = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int BLACK     = 0;

// timers
const int SUPER_MAX   = 500;
const int ONE_UP_MAX  = 13;
const int PELLET_MAX  = 8;
const int PACMAN_MAX  = 8;
const int GHOST_MAX   = 10;
const int RUN_MAX     = 16;
const int DEAD_MAX    = 3;
const int MODE_MAX    = 1000;

// Ghost Names
const int BLINKY = 0;
const int PINKY  = 1;
const int INKY   = 2;
const int CLYDE  = 3;

#endif
