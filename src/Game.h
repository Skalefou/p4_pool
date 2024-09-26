//
// Created by user on 26/09/24.
//

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Window.h"

int gameInit();
void gameClose();
void gameRuntime();

typedef struct {
    Window window;
} Game;

extern Game game;

#endif //GAME_H
