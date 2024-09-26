#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "Game.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    if (SDLNet_Init() != 0) {
        printf("SDLNet_Init Error: %s\n", SDLNet_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    if (TTF_Init() != 0) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDLNet_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    gameRuntime();

    TTF_Quit();
    SDLNet_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}