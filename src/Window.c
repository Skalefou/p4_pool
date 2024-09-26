#include "Game.h"
#include "Window.h"

int windowInit() {
    game.window.screen = SDL_CreateWindow("Puissance 4",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH_DEFAULT, SCREEN_HEIGHT_DEFAULT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
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
}
