#include "includes.h"

using namespace std;

// check for user input every time the wait timer reaches 0
void pacman::move()
{
    if(wait)
        wait--;
    else
    {
        getdirection();
        if(testforcollision() == false)
        {
            // replace old coordinates with a space
            SetCursorPosition(yold, xold);
            cout << level[yold][xold];
            // if the player picked up a pellet
            if(level[y][x] != ' ')
            {
                if(level[y][x] == 'o')
                {
                    scoreinc = 50;
                    super = SUPERMAX;
                }
                else
                    scoreinc = 10;
                printscore();
                level[y][x] = ' ';
                left--;
            }
            show();
            dirold = dir;
            wait = PACMANMAX;
            checkfordeath();
        }
    }
}

void pacman::getdirection()
{
    dir = 'x';
    // check if the user has entered 'w', 'a', 's' or 'd'
    if(_kbhit())
        dir = tolower(_getch());
    // if not, try moving in the same direction as before
    if(!strchr(ALLDIRS, dir))
        dir = dirold;
}

bool pacman::testforcollision()
{
    // save old coordinates
    xold = x;
    yold = y;
    // if the character in front of the player is a space, move in the appropriate direction
    switch(dir)
    {
    case 'a':
    {
        // if travelling through the tunnel
        if(x == 0)
        {
            x = LEVELWIDTH - 1;
            icon = ICONS[1];
        }
        else if(strchr(NOCOLLISIONTILES, level[y][x - 1]))
        {
            x--;
            icon = ICONS[1];
        }
        break;
    }
    case 'd':
    {
        // if travelling through the tunnel
        if(x == LEVELWIDTH - 1)
        {
            x = 0;
            icon = ICONS[3];
        }
        else if(strchr(NOCOLLISIONTILES, level[y][x + 1]))
        {
            x++;
            icon = ICONS[3];
        }
        break;
    }
    case 'w':
    {
        if(strchr(NOCOLLISIONTILES, level[y - 1][x]))
        {
            y--;
            icon = ICONS[0];
        }
        break;
    }
    case 's':
    {
        if(strchr(NOCOLLISIONTILES, level[y + 1][x]))
        {
            y++;
            icon = ICONS[2];
        }
    }
    }
    // if coordinates were not changed, there was a collision
    if(x == xold && y == yold)
        return true;
    return false;
}

void pacman::printscore()
{
    // gain a life every time the score crosses a multiple of 10000
    if(score / 10000 < (score + scoreinc) / 10000)
    {
        lives++;
        printlives();
    }
    score += scoreinc;
    SetTextColor(WHITE);
    SetCursorPosition(-2, 0);
    if(score == 0)
        cout << setw(7) << "00";
    else
        cout << setw(7) << score;
    if(score > hiscore)
    {
        hiscore = score;
        cout << setw(11) << hiscore;
    }
}

void pacman::printlives()
{
    SetTextColor(color);
    SetCursorPosition(LEVELHEIGHT, 2);
    for(int i = 1; i < lives; i++)
        cout << ICONS[1] << " ";
    cout << " ";
}

void pacman::printkillscore()
{
    killcount++;
    scoreinc = 200 * pow(2, killcount - 1);
    int length = floor(log10(scoreinc)) + 1;
    int killx = x - 1;
    if(x == 0)
        killx = x;
    if(x > LEVELWIDTH - length)
        killx = LEVELWIDTH - length;
    SetTextColor(CYAN);
    SetCursorPosition(y, killx);
    cout << scoreinc;
    printscore();
    Sleep(750);
    SetCursorPosition(y, killx);
    for(int i = killx; i < killx + length; i++)
    {
        SetTextColor(DARKBLUE);
        if(level[y][i] == char(250))
            SetTextColor(WHITE);
        if(level[y][i] == 'o')
            SetTextColor(pelletcolor);
        cout << level[y][i];
    }
    show();
}

void pacman::dead()
{
    Sleep(1000);
    hideall();
    for(int i = 0; i < 8; i++)
    {
        icon = ICONS[i % 4];
        show();
        Sleep(100);
    }
    hide();
    Sleep(500);
    lives--;
    if(lives != 0)
    {
        initall();
        showall();
        printlives();
        dirold = 'a';
        printready();
    }
    else
        gameover();
}

void pacman::show()
{
    SetTextColor(color);
    SetCursorPosition(y, x);
    cout << icon;
}

void pacman::hide()
{
    SetCursorPosition(y, x);
    cout << level[y][x];
}
