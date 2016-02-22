#ifndef GHOST_H
#define GHOST_H

class Game;

class Ghost {
private:
    int y, x;
    int yInit, xInit;
    int wait;
    int color;
    int colorInit;
    char dir;
    char dirOld;
    char dirOpp;
    char mode;
    char modeOld;
    char icon;

    Game *game;

public:
    Ghost(Game *const g);
    void Move(int, int);
    void TargetObject(bool[4]);
    void RandomDirection();
    bool TestForCollision();
    void ChangeCoords();
    void GetOpposite();
    void Dead();
    void Show();
    void Hide();

    int GetY()         { return y;         }
    int GetX()         { return x;         }
    int GetYInit()     { return yInit;     }
    int GetXInit()     { return xInit;     }
    int GetColor()     { return color;     }
    int GetColorInit() { return colorInit; }
    char GetMode()     { return mode;      }

    void SetY(int y)         { this->y = y;   }
    void SetX(int x)         { this->x = x;   }
    void SetYInit(int y)     { yInit = y;     }
    void SetXInit(int x)     { xInit = x;     }
    void SetWait(int w)      { wait = w;      }
    void SetColor(int c)     { color = c;     }
    void SetColorInit(int c) { colorInit = c; }
    void SetDirOpp(char d)   { dirOpp = d;    }
    void SetMode(char m)     { mode = m;      }
    void SetModeOld(char m)  { modeOld = m;   }
    void SetIcon(char i)     { icon = i;      }
};

#endif
