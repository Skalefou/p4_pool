//
// Created by user on 26/09/24.
//

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Window.h"
#include "Graphic.h"
#include "Map.h"

int gameInit();
void gameClickEvent(const int x, const int y);
void gameClose();
void gameRuntime();

typedef struct {
    Window window;
    Graphic graphic;
    int turnPlayer;
    Map map;
} Game;

extern Game game;

#endif //GAME_H
