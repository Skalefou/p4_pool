//
// Created by user on 26/09/24.
//

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Window.h"
#include "Graphic.h"
#include "Map.h"
#include "Config.h"

int gameInit();
void gameClickEvent(const int x, const int y);
void gameReset();
int gameIsWinHorizontal();
int gameIsWinVertical();
int gameIsWinDiagonal();
int gameIsWin();
void gameClose();
void gameRuntime();

typedef struct {
    Window window;
    Graphic graphic;
    int turnPlayer;
    int playerWin;
    Map map;
    Config config;
} Game;

extern Game game;

#endif //GAME_H
