#ifndef PACMAN_H
#define PACMAN_H

class pacman
{
public:
    int y, x;
    int yold, xold;
    int yinit, xinit;
    int wait;
    int left;
    int score;
    int scoreinc;
    int hiscore;
    int lives;
    int super;
    int killcount;
    int color;
    char dir;
    char dirold;
    char icon;

    void move();
    void getdirection();
    bool testforcollision();
    void printscore();
    void printlives();
    void printkillscore();
    void dead();
    void show();
    void hide();
};

#endif
