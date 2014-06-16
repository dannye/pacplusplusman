#include "includes.h"

using namespace std;

void moveghosts()
{
    // check for ghost mode changes
    if(player.super == SUPERMAX)
    {
        player.killcount = 0;
        if(blinky.mode != 'd')
            blinky.color = BLUE;
        if(pinky.mode != 'd')
            pinky.color = BLUE;
        if(inky.mode != 'd')
            inky.color = BLUE;
        if(clyde.mode != 'd')
            clyde.color = BLUE;
        if(blinky.mode == 's' || blinky.mode == 'c')
        {
            blinky.mode = 'r';
        }
        if(pinky.mode == 's' || pinky.mode == 'c')
        {
            pinky.mode = 'r';
        }
        if(inky.mode == 's' || inky.mode == 'c')
        {
            inky.mode = 'r';
        }
        if(clyde.mode == 's' || clyde.mode == 'c')
        {
            clyde.mode = 'r';
        }
        showall();
    }
    if(player.left == 235 && pinky.mode == 'w')
        pinky.mode = 'e';
    if(player.left == 200 && inky.mode == 'w')
        inky.mode = 'e';
    if(player.left == 165 && clyde.mode == 'w')
        clyde.mode = 'e';
    blinky.move(player.y, player.x);
    pinky.move(player.y, player.x);
    inky.move(player.y, player.x);
    clyde.move(player.y, player.x);
    showall();
    checkfordeath();
}

void updatetimers()
{
    // handle super pacman
    if(player.super)
    {
        player.super--;
        if(player.super <= 112 && player.super % 28 == 0)
        {
            if(blinky.color == BLUE)
                blinky.color = WHITE;
            if(pinky.color == BLUE)
                pinky.color = WHITE;
            if(inky.color == BLUE)
                inky.color = WHITE;
            if(clyde.color == BLUE)
                clyde.color = WHITE;
            showall();
        }
        if(player.super <= 98 && (player.super + 14) % 28 == 0)
        {
            if(blinky.color == WHITE && blinky.mode != 'd' && blinky.mode != 'n')
                blinky.color = BLUE;
            if(pinky.color == WHITE && pinky.mode != 'd' && pinky.mode != 'n')
                pinky.color = BLUE;
            if(inky.color == WHITE && inky.mode != 'd' && inky.mode != 'n')
                inky.color = BLUE;
            if(clyde.color == WHITE && clyde.mode != 'd' && clyde.mode != 'n')
                clyde.color = BLUE;
            showall();
        }
        if(!player.super)
        {
            if(blinky.mode != 'd' && blinky.mode != 'n')
                blinky.color = blinky.colorinit;
            if(pinky.mode != 'd' && pinky.mode != 'n')
                pinky.color = pinky.colorinit;
            if(inky.mode != 'd' && inky.mode != 'n')
                inky.color = inky.colorinit;
            if(clyde.mode != 'd' && clyde.mode != 'n')
                clyde.color = clyde.colorinit;
            if(blinky.mode == 'r')
            {
                blinky.mode = 'c';
                blinky.modeold = 'r';
            }
            if(pinky.mode == 'r')
            {
                pinky.mode = 'c';
                pinky.modeold = 'r';
            }
            if(inky.mode == 'r')
            {
                inky.mode = 'c';
                inky.modeold = 'r';
            }
            if(clyde.mode == 'r')
            {
                clyde.mode = 'c';
                clyde.modeold = 'r';
            }
            showall();
        }
    }
    // handle flashing 1UP
    if(oneuptimer)
        oneuptimer--;
    else
    {
        if(oneupcolor == WHITE)
            oneupcolor = BLACK;
        else
            oneupcolor = WHITE;
        SetTextColor(oneupcolor);
        SetCursorPosition(-3, 3);
        cout << "1UP";
        oneuptimer = ONEUPMAX;
    }
    // handle flashing super pellets
    if(pellettimer)
        pellettimer--;
    else
    {
        if(pelletcolor == WHITE)
            pelletcolor = BLACK;
        else
            pelletcolor = WHITE;
        SetTextColor(pelletcolor);
        one.print();
        two.print();
        three.print();
        four.print();
        showall();
        pellettimer = PELLETMAX;
    }
    // handle ghost chase/scatter mode
    if(ghostmode)
    {
        ghostmode--;
        if (ghostmode == MODEMAX / 4)
        {
            if (blinky.mode == 'c')
                blinky.mode = 's';
            if (pinky.mode == 'c')
                pinky.mode = 's';
            if (inky.mode == 'c')
                inky.mode = 's';
            if (clyde.mode == 'c')
                clyde.mode = 's';
        }
    }
    else
    {
        if (blinky.mode == 's')
            blinky.mode = 'c';
        if (pinky.mode == 's')
            pinky.mode = 'c';
        if (inky.mode == 's')
            inky.mode = 'c';
        if (clyde.mode == 's')
            clyde.mode = 'c';
        ghostmode = MODEMAX;
    }
    Sleep(15);
}

void checkfordeath()
{
    if(player.x == blinky.x && player.y == blinky.y && blinky.mode != 'd' && blinky.mode != 'n')
    {
        if(blinky.mode != 'r')
            player.dead();
        else
        {
            player.printkillscore();
            blinky.dead();
        }
    }
    if(player.x == pinky.x && player.y == pinky.y && pinky.mode != 'd' && pinky.mode != 'n')
    {
        if(pinky.mode != 'r')
            player.dead();
        else
        {
            player.printkillscore();
            pinky.dead();
        }
    }
    if(player.x == inky.x && player.y == inky.y && inky.mode != 'd' && inky.mode != 'n')
    {
        if(inky.mode != 'r')
            player.dead();
        else
        {
            player.printkillscore();
            inky.dead();
        }
    }
    if(player.x == clyde.x && player.y == clyde.y && clyde.mode != 'd' && clyde.mode != 'n')
    {
        if(clyde.mode != 'r')
            player.dead();
        else
        {
            player.printkillscore();
            clyde.dead();
        }
    }
}

void showall()
{
    player.show();
    blinky.show();
    pinky.show();
    inky.show();
    clyde.show();
}

void hideall()
{
    player.hide();
    blinky.hide();
    pinky.hide();
    inky.hide();
    clyde.hide();
}

void initall()
{
    player.y = player.yinit;
    player.x = player.xinit;
    player.color = YELLOW;
    player.icon = ICONS[1];
    player.dirold = 'a';
    player.wait = 0;
    player.super = 0;
    blinky.y = blinky.yinit;
    blinky.x = blinky.xinit;
    blinky.color = blinky.colorinit;
    blinky.mode = 'c';
    blinky.modeold = 'c';
    blinky.wait = 0;
    pinky.y = pinky.yinit;
    pinky.x = pinky.xinit;
    pinky.color = pinky.colorinit;
    pinky.mode = 'w';
    pinky.wait = 0;
    inky.y = inky.yinit;
    inky.x = inky.xinit;
    inky.color = inky.colorinit;
    inky.mode = 'w';
    inky.wait = 0;
    clyde.y = clyde.yinit;
    clyde.x = clyde.xinit;
    clyde.color = clyde.colorinit;
    clyde.mode = 'w';
    clyde.wait = 0;
    if(player.left <= 235)
        pinky.mode = 'e';
    if(player.left <= 200)
        inky.mode = 'e';
    if(player.left <= 165)
        clyde.mode = 'e';
}
