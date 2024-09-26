
#include "Game.h"

Game game;

int gameInit() {
    if (windowInit()) {
        return 1;
    }

    return 0;
}

void gameClose() {
    windowClose();
}

void gameRuntime() {
    if (gameInit()) {
        gameClose();
        return;
    }


    gameClose();
}
