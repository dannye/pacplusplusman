#include "includes.h"

using namespace std;

void moveghosts()
{
    // check for ghost mode changes
    if(player.super == SUPERMAX)
    {
        player.killcount = 0;
        for(int i = 0; i < 4; i++)
        {
            if(ghosts[i].mode != 'd')
                ghosts[i].color = BLUE;
            if(ghosts[i].mode == 's' || ghosts[i].mode == 'c')
                ghosts[i].mode = 'r';
        }
        showall();
    }
    if(player.left == 235 && ghosts[1].mode == 'w')
        ghosts[INKY].mode = 'e';
    if(player.left == 200 && ghosts[2].mode == 'w')
        ghosts[PINKY].mode = 'e';
    if(player.left == 165 && ghosts[3].mode == 'w')
        ghosts[CLYDE].mode = 'e';
    for(int i = 0; i < 4; i++)
       ghosts[i].move(player.y, player.x);
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
            for(int i = 0; i < 4; i++)
                if(ghosts[i].color == BLUE)
                    ghosts[i].color = WHITE;
            showall();
        }
        if(player.super <= 98 && (player.super + 14) % 28 == 0)
        {
            for(int i = 0; i < 4; i++)
                if(ghosts[i].color == WHITE && ghosts[i].mode != 'd' && ghosts[i].mode != 'n')
                    ghosts[i].color = BLUE;
            showall();
        }
        if(!player.super)
        {
            for(int i = 0; i < 4; i++)
            {
                if(ghosts[i].mode != 'd' && ghosts[i].mode != 'n')
                    ghosts[i].color = ghosts[i].colorinit;
                if(ghosts[i].mode == 'r')
                {
                    ghosts[i].modeold = ghosts[i].mode;
                    ghosts[i].mode = 'c';
                }
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
        for(int i = 0; i < 4; i++)
            pellets[i].print();
        showall();
        pellettimer = PELLETMAX;
    }
    // handle ghost chase/scatter mode
    if(ghostmode)
    {
        ghostmode--;
        if(ghostmode == MODEMAX / 4)
            for(int i = 0; i < 4; i++)
            if(ghosts[i].mode == 'c')
                    ghosts[i].mode = 's';
    }
    else
    {
        for(int i = 0; i < 4; i++)
            if(ghosts[i].mode == 's')
                ghosts[i].mode = 'c';
        ghostmode = MODEMAX;
    }
    Sleep(15);
}

void checkfordeath()
{
    for(int i = 0; i < 4; i++)
        if(player.x == ghosts[i].x && player.y == ghosts[i].y && ghosts[i].mode != 'd' && ghosts[i].mode != 'n')
        {
            if(ghosts[i].mode != 'r')
                player.dead();
            else
            {
                player.printkillscore();
                ghosts[i].dead();
            }
        }
}

void showall()
{
    player.show();
    for(int i = 0; i < 4; i++)
        ghosts[i].show();
}

void hideall()
{
    player.hide();
    for(int i = 0; i < 4; i++)
        ghosts[i].hide();
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
    for(int i = 0; i < 4; i++)
    {
        ghosts[i].y = ghosts[i].yinit;
        ghosts[i].x = ghosts[i].xinit;
        ghosts[i].color = ghosts[i].colorinit;
        ghosts[i].mode = 'w';
        ghosts[i].wait = 0;
    }
    ghosts[BLINKY].mode = 'c';
    ghosts[BLINKY].modeold = 'c';
    if(player.left <= 235)
        ghosts[INKY].mode = 'e';
    if(player.left <= 200)
        ghosts[PINKY].mode = 'e';
    if(player.left <= 165)
        ghosts[CLYDE].mode = 'e';
}
