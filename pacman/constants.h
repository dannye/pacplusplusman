#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef INCLUDES_H

#include <Windows.h>

#endif

// level properties
const int LEVELHEIGHT = 31;
const int LEVELWIDTH  = 28;
const char NOCOLLISIONTILES[3] = {' ','o','\xfa'};
const int GATEX = 13;
const int GATEY = 12;

// directions
const char ALLDIRS[4] = {'w','a','s','d'};
const char ICONS[4]   = {'v','>','^','<'};

// colors
const int WHITE    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int RED      = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int BLUE     = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int DARKBLUE = FOREGROUND_BLUE;
const int CYAN     = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int MAGENTA  = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int YELLOW   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int BLACK    = 0;

// timers
const int SUPERMAX  = 500;
const int ONEUPMAX  = 13;
const int PELLETMAX = 8;
const int PACMANMAX = 8;
const int GHOSTMAX  = 10;
const int RUNMAX    = 16;
const int DEADMAX   = 3;
const int MODEMAX   = 1000;

// Ghost Names
const int BLINKY = 0;
const int PINKY = 1;
const int INKY = 2;
const int CLYDE = 3;

#endif
