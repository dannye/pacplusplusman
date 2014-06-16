#ifndef GHOST_H
#define GHOST_H

class ghost
{
public:
    int y, x;
    int yinit, xinit;
    int wait;
    int color;
    int colorinit;
    char dir;
    char dirold;
    char diropp;
    char mode;
    char modeold;
    bool up;
    bool left;
    bool down;
    bool right;

    void move(int, int);
    void targetobject();
    void randomdirection();
    bool testforcollision();
    void changecoords();
    void getopposite();
    void dead();
    void show();
    void hide();
};

#endif
