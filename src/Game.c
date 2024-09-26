
#include "Game.h"

Game game;

int gameInit() {
    if (windowInit()) {
        return 1;
    }

    if (graphicInit()) {
        return 1;
    }

    if (mapInit(7, 6)) {
        return 1;
    }

    game.turnPlayer = 0;
    return 0;
}

void gameClose() {
    mapClose();
    graphicClose();
    windowClose();
}

void gameClickEvent(const int x, const int y) {
    int columnClick = x / 64;
    if (columnClick >= 0 && columnClick < game.map.sizeX) {
        if (isLimitColumn(columnClick)) {
            setJeton(game.turnPlayer + 1, columnClick);
            game.turnPlayer = (game.turnPlayer + 1) % 2;
        }
    }
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
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= 0 && mouseX < game.window.width && mouseY >= 0 && mouseY < game.window.height) {
                        gameClickEvent(mouseX, mouseY);
                    }
                }
            }
        }

        // Logique de jeu


        // Affichage
        SDL_RenderClear(game.window.renderer);
        graphicDisplayGrid();
        graphicsDisplayJeton();
        graphicDisplayTurn(game.turnPlayer);
        SDL_RenderPresent(game.window.renderer);
    }

    gameClose();
}
