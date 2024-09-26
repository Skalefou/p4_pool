
#include "Game.h"

Game game;

int gameInit() {
    if (windowInit()) {
        return 1;
    }

    if (graphicInit()) {
        return 1;
    }

    return 0;
}

void gameClose() {
    graphicClose();
    windowClose();
}

void gameRuntime() {
    if (gameInit()) {
        gameClose();
        return;
    }

    SDL_Event event;
    int run = 1;

    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    run = 0;
                }
            }
        }

        SDL_RenderClear(game.window.renderer);

        graphicDisplayGrid();

        SDL_RenderPresent(game.window.renderer);
    }

    gameClose();
}
