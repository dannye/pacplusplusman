// main.cpp

#include "includes.h"

using namespace std;

void mainloop();

int main()
{
    srand(time(0));
    SetConsoleTitle("PAC++MAN");
    SetWindowSize(LEVELHEIGHT + 4, LEVELWIDTH);
    SetCursorVisibility(false);
    player.hiscore = 0;
    mainloop();
    return 0;
}

void mainloop()
{
    player.score = 0;
    player.lives = 3;
    for(int levelnum = 1; levelnum <= 255; levelnum++)
    {
        loadlevel();
        // while there are still dots on the screen,
        while(player.left != 0)
        {
            player.move();
            moveghosts();
            updatetimers();
        }
        nextlevel();
    }
}
