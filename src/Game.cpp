#include <iostream>
#include <Windows.h>

#include "Constants.h"

#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Pellet.h"
#include "SetConsoleAttributes.h"

using namespace std;

Game::Game() {
    SetWindowTitle("PAC++MAN");
    SetWindowSize(LEVEL_HEIGHT + 4, LEVEL_WIDTH);
    SetCursorVisibility(false);
    player = new Pacman(this);
    for (int i = 0; i < 4; ++i) {
        ghosts[i] = new Ghost(this);
        pellets[i] = new Pellet(this);
    }
}

Game::~Game() {
    delete player;
    for (int i = 0; i < 4; ++i) {
        delete ghosts[i];
        delete pellets[i];
    }
}

void Game::Go() {
    while (true) {
        MainLoop();
    }
}

void Game::MainLoop() {
    player->SetScore(0);
    player->SetLives(3);
    bool gameOver = false;
    for (int levelNum = 1; levelNum <= 255; ++levelNum) {
        LoadLevel();
        // while there are still dots on the screen,
        while (player->GetLeft() != 0) {
            player->Move();
            CheckForDeath();
            if (!player->GetLives()) {
                gameOver = true;
                break;
            }
            MoveGhosts();
            CheckForDeath();
            if (!player->GetLives()) {
                gameOver = true;
                break;
            }
            UpdateTimers();
        }
        if (gameOver) {
            break;
        }
        NextLevel();
    }
}

void Game::LoadLevel() {
    char levelMap[LEVEL_HEIGHT][LEVEL_WIDTH + 1] = {
        "1555555555555555555555555552",
        "6............^^............6",
        "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
        "67^  ^.^   ^.^^.^   ^.^  ^86",
        "6.#%%$.#%%%$.#$.#%%%$.#%%$.6",
        "6..........................6",
        "6.!%%@.!@.!%%%%%%@.!@.!%%@.6",
        "6.#%%$.^^.#%%@!%%$.^^.#%%$.6",
        "6......^^....^^....^^......6",
        "355552.^#%%@ ^^ !%%$^.155554",
        "     6.^!%%$ #$ #%%@^.6     ",
        "     6.^^    B     ^^.6     ",
        "     6.^^ 155&&552 ^^.6     ",
        "555554.#$ 6      6 #$.355555",
        "      .   6I   C 6   .      ",
        "555552.!@ 6  P   6 !@.155555",
        "     6.^^ 35555554 ^^.6     ",
        "     6.^^          ^^.6     ",
        "     6.^^ !%%%%%%@ ^^.6     ",
        "155554.#$ #%%@!%%$ #$.355552",
        "6............^^............6",
        "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
        "6.#%@^.#%%%$.#$.#%%%$.^!%$.6",
        "69..^^.......X .......^^..06",
        "6%@.^^.!@.!%%%%%%@.!@.^^.!%6",
        "6%$.#$.^^.#%%@!%%$.^^.#$.#%6",
        "6......^^....^^....^^......6",
        "6.!%%%%$#%%@.^^.!%%$#%%%%@.6",
        "6.#%%%%%%%%$.#$.#%%%%%%%%$.6",
        "6..........................6",
        "3555555555555555555555555554"};
    char curChar;
    SetTextColor(WHITE);
    SetCursorPosition(-3, 3);
    cout << "1UP";
    SetCursorPosition(-3, 9);
    cout << "HIGH SCORE";
    player->PrintScore(0);
    SetCursorPosition(0, 0);
    player->SetLeft(0);
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            curChar = levelMap[y][x];
            SetTextColor(DARK_BLUE);
            switch (curChar) {
            case 'X':
                player->SetYInit(y);
                player->SetXInit(x);
                level[y][x] = ' ';
                break;
            case 'B':
                ghosts[BLINKY]->SetYInit(y);
                ghosts[BLINKY]->SetXInit(x);
                ghosts[BLINKY]->SetColorInit(RED);
                ghosts[BLINKY]->SetDirOpp('s');
                level[y][x] = ' ';
                break;
            case 'P':
                ghosts[PINKY]->SetYInit(y);
                ghosts[PINKY]->SetXInit(x);
                ghosts[PINKY]->SetColorInit(MAGENTA);
                level[y][x] = ' ';
                break;
            case 'I':
                ghosts[INKY]->SetYInit(y);
                ghosts[INKY]->SetXInit(x);
                ghosts[INKY]->SetColorInit(CYAN);
                level[y][x] = ' ';
                break;
            case 'C':
                ghosts[CLYDE]->SetYInit(y);
                ghosts[CLYDE]->SetXInit(x);
                ghosts[CLYDE]->SetColorInit(YELLOW);
                level[y][x] = ' ';
                break;
            case '7':
                pellets[0]->SetY(y);
                pellets[0]->SetX(x);
                SetTextColor(WHITE);
                level[y][x] = 'o';
                player->SetLeft(player->GetLeft() + 1);
                break;
            case '8':
                pellets[1]->SetY(y);
                pellets[1]->SetX(x);
                SetTextColor(WHITE);
                level[y][x] = 'o';
                player->SetLeft(player->GetLeft() + 1);
                break;
            case '9':
                pellets[2]->SetY(y);
                pellets[2]->SetX(x);
                SetTextColor(WHITE);
                level[y][x] = 'o';
                player->SetLeft(player->GetLeft() + 1);
                break;
            case '0':
                pellets[3]->SetY(y);
                pellets[3]->SetX(x);
                SetTextColor(WHITE);
                level[y][x] = 'o';
                player->SetLeft(player->GetLeft() + 1);
                break;
            case '.':
                SetTextColor(WHITE);
                level[y][x] = char(250);
                player->SetLeft(player->GetLeft() + 1);
                break;
            case ' ':
                level[y][x] = curChar;
                break;
            case '&':
                SetTextColor(WHITE);
                curChar = '%';
            }
            if (curChar == '1') {
                level[y][x] = char(201);
            }
            else if (curChar == '2') {
                level[y][x] = char(187);
            }
            else if (curChar == '3') {
                level[y][x] = char(200);
            }
            else if (curChar == '4') {
                level[y][x] = char(188);
            }
            else if (curChar == '5') {
                level[y][x] = char(205);
            }
            else if (curChar == '6') {
                level[y][x] = char(186);
            }
            else if (curChar == '!') {
                level[y][x] = char(218);
            }
            else if (curChar == '@') {
                level[y][x] = char(191);
            }
            else if (curChar == '#') {
                level[y][x] = char(192);
            }
            else if (curChar == '$') {
                level[y][x] = char(217);
            }
            else if (curChar == '%') {
                level[y][x] = char(196);
            }
            else if (curChar == '^') {
                level[y][x] = char(179);
            }
            cout << level[y][x];
        }
        SetCursorPosition(y + 1, 0);
    }
    InitAll();
    ShowAll();
    player->PrintLives();
    PrintReady();
}

void Game::NextLevel() {
    Sleep(1000);
    HideAll();
    SetCursorPosition(12, 13);
    cout << "  ";
    for (int i = 0; i < 4; ++i) {
        SetScreenColor(WHITE);
        player->Show();
        Sleep(200);
        SetScreenColor(DARK_BLUE);
        player->Show();
        Sleep(200);
    }
    SetCursorPosition(0, 0);
    InitAll();
}

void Game::PrintReady() {
    SetTextColor(YELLOW);
    SetCursorPosition(17, 11);
    cout << "READY!";
    Sleep(2000);
    SetCursorPosition(17, 11);
    cout << "      ";
}

void Game::PrintGameOver() {
    SetCursorPosition(17, 9);
    SetTextColor(RED);
    cout << "GAME  OVER";
    Sleep(1000);
}

void Game::MoveGhosts() {
    // check for ghost mode changes
    if (player->GetSuper() == SUPER_MAX) {
        player->SetKillCount(0);
        for (int i = 0; i < 4; ++i) {
            if (ghosts[i]->GetMode() != 'd') {
                ghosts[i]->SetColor(BLUE);
            }
            if (ghosts[i]->GetMode() == 's' || ghosts[i]->GetMode() == 'c') {
                ghosts[i]->SetMode('r');
            }
        }
        ShowAll();
    }
    if (player->GetLeft() == 235 && ghosts[PINKY]->GetMode() == 'w') {
        ghosts[PINKY]->SetMode('e');
    }
    if (player->GetLeft() == 200 && ghosts[INKY]->GetMode() == 'w') {
        ghosts[INKY]->SetMode('e');
    }
    if (player->GetLeft() == 165 && ghosts[CLYDE]->GetMode() == 'w') {
        ghosts[CLYDE]->SetMode('e');
    }
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Move(player->GetY(), player->GetX());
    }
    ShowAll();
}

void Game::UpdateTimers() {
    // handle super pacman
    if (player->GetSuper()) {
        player->SetSuper(player->GetSuper() - 1);
        if (player->GetSuper() <= 112 && player->GetSuper() % 28 == 0) {
            for (int i = 0; i < 4; ++i)
            if (ghosts[i]->GetColor() == BLUE) {
                ghosts[i]->SetColor(WHITE);
            }
            ShowAll();
        }
        if (player->GetSuper() <= 98 && (player->GetSuper() + 14) % 28 == 0) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->GetColor() == WHITE && ghosts[i]->GetMode() != 'd' && ghosts[i]->GetMode() != 'n') {
                    ghosts[i]->SetColor(BLUE);
                }
            }
            ShowAll();
        }
        if (!player->GetSuper()) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->GetMode() != 'd' && ghosts[i]->GetMode() != 'n') {
                    ghosts[i]->SetColor(ghosts[i]->GetColorInit());
                }
                if (ghosts[i]->GetMode() == 'r') {
                    ghosts[i]->SetModeOld(ghosts[i]->GetMode());
                    ghosts[i]->SetMode('c');
                }
            }
            ShowAll();
        }
    }
    // handle flashing 1UP
    if (oneUpTimer) {
        --oneUpTimer;
    }
    else {
        if (oneUpColor == WHITE) {
            oneUpColor = BLACK;
        }
        else {
            oneUpColor = WHITE;
        }
        SetTextColor(oneUpColor);
        SetCursorPosition(-3, 3);
        cout << "1UP";
        oneUpTimer = ONE_UP_MAX;
    }
    // handle flashing super pellets
    if (pelletTimer) {
        --pelletTimer;
    }
    else {
        if (pelletColor == WHITE) {
            pelletColor = BLACK;
        }
        else {
            pelletColor = WHITE;
        }
        SetTextColor(pelletColor);
        for (int i = 0; i < 4; ++i) {
            pellets[i]->Print();
        }
        ShowAll();
        pelletTimer = PELLET_MAX;
    }
    // handle ghost chase/scatter mode
    if (ghostModeTimer) {
        --ghostModeTimer;
        if (ghostModeTimer == MODE_MAX / 4) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->GetMode() == 'c') {
                    ghosts[i]->SetMode('s');
                }
            }
        }
    }
    else {
        for (int i = 0; i < 4; ++i) {
            if (ghosts[i]->GetMode() == 's') {
                ghosts[i]->SetMode('c');
            }
        }
        ghostModeTimer = MODE_MAX;
    }
    Sleep(15);
}

void Game::CheckForDeath() {
    for (int i = 0; i < 4; ++i) {
        if (player->GetX() == ghosts[i]->GetX() && player->GetY() == ghosts[i]->GetY() &&
            ghosts[i]->GetMode() != 'd' && ghosts[i]->GetMode() != 'n') {
            if (ghosts[i]->GetMode() != 'r') {
                player->Dead();
            }
            else {
                player->PrintKillScore();
                ghosts[i]->Dead();
            }
        }
    }
}

void Game::ShowAll() {
    player->Show();
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Show();
    }
}

void Game::HideAll() {
    player->Hide();
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Hide();
    }
}

void Game::InitAll() {
    player->SetY(player->GetYInit());
    player->SetX(player->GetXInit());
    player->SetColor(YELLOW);
    player->SetIcon(ICONS[1]);
    player->SetDirOld('a');
    player->SetWait(0);
    player->SetSuper(0);
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->SetY(ghosts[i]->GetYInit());
        ghosts[i]->SetX(ghosts[i]->GetXInit());
        ghosts[i]->SetColor(ghosts[i]->GetColorInit());
        ghosts[i]->SetMode('w');
        ghosts[i]->SetWait(0);
        ghosts[i]->SetIcon(GHOST_ICON);
    }
    ghosts[BLINKY]->SetMode('c');
    ghosts[BLINKY]->SetModeOld('c');
    if (player->GetLeft() <= 235) {
        ghosts[PINKY]->SetMode('e');
    }
    if (player->GetLeft() <= 200) {
        ghosts[INKY]->SetMode('e');
    }
    if (player->GetLeft() <= 165) {
        ghosts[CLYDE]->SetMode('e');
    }
}
