#include "Game.h"
#include "Window.h"

int windowInit(const int rows, const int columns) {
    game.window.width = 64*rows;
    game.window.height = 64*columns + HEIGHT_BANDEAU;

    game.window.screen = SDL_CreateWindow("Puissance 4",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game.window.width, game.window.height,
        SDL_WINDOW_SHOWN);
    if (game.window.screen == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    game.window.renderer = SDL_CreateRenderer(game.window.screen, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (game.window.renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

void windowClose() {
    if (game.window.renderer != NULL) {
        SDL_DestroyRenderer(game.window.renderer);
    }
    if (game.window.screen != NULL) {
        SDL_DestroyWindow(game.window.screen);
    }
    game.window.width = 0;
    game.window.height = 0;
}
