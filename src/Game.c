
#include "Game.h"

Game game;

int gameInit() {
    if (configInit()) {
        return 1;
    }

    if (windowInit(game.config.rows, game.config.columns)) {
        return 1;
    }

    if (graphicInit()) {
        return 1;
    }

    if (mapInit(game.config.rows, game.config.columns)) {
        return 1;
    }

    game.turnPlayer = 0;
    game.playerWin = 0;
    return 0;
}

void gameClose() {
    configClose();
    mapClose();
    graphicClose();
    windowClose();
}

void gameClickEvent(const int x, const int y) {
    int columnClick = x / 64;
    if (columnClick >= 0 && columnClick < game.map.sizeX) {
        if (isLimitColumn(columnClick)) {
            setJeton(game.turnPlayer + 1, columnClick);
            game.turnPlayer = game.turnPlayer < game.config.playerNb-1 ? game.turnPlayer + 1 : 0;
            game.playerWin = gameIsWin();
        }
    }
}

void gameReset() {
    mapReset();
    game.turnPlayer = 0;
    game.playerWin = 0;
}

int gameIsWinVertical() {
    for (int x = 0; x < game.map.sizeX; x++) {
        for (int i = 0; i <= game.map.sizeY - game.config.winNumberJeton; i++) {
            int count = 1;
            for (int j = 1; j < game.config.winNumberJeton; j++) {
                if (game.map.grid[x][i] != 0 && game.map.grid[x][i] == game.map.grid[x][i + j]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == game.config.winNumberJeton) {
                return game.map.grid[x][i];
            }
        }
    }
    return 0;
}

int gameIsWinHorizontal() {
    for (int y = 0; y < game.map.sizeY; y++) {
        for (int i = 0; i <= game.map.sizeX - game.config.winNumberJeton; i++) {
            int count = 1;
            for (int j = 1; j < game.config.winNumberJeton; j++) {
                if (game.map.grid[i][y] != 0 && game.map.grid[i][y] == game.map.grid[i + j][y]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == game.config.winNumberJeton) {
                return game.map.grid[i][y];
            }
        }
    }
    return 0;
}

int gameIsWinDiagonal() {
    for (int x = 0; x <= game.map.sizeX - game.config.winNumberJeton; x++) {
        for (int y = 0; y <= game.map.sizeY - game.config.winNumberJeton; y++) {
            int count = 1;
            for (int j = 1; j < game.config.winNumberJeton; j++) {
                if (game.map.grid[x][y] != 0 && game.map.grid[x][y] == game.map.grid[x + j][y + j]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == game.config.winNumberJeton) {
                return game.map.grid[x][y];
            }
        }
    }
    for (int x = 0; x <= game.map.sizeX - game.config.winNumberJeton; x++) {
        for (int y = game.config.winNumberJeton - 1; y < game.map.sizeY; y++) {
            int count = 1;
            for (int j = 1; j < game.config.winNumberJeton; j++) {
                if (game.map.grid[x][y] != 0 && game.map.grid[x][y] == game.map.grid[x + j][y - j]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == game.config.winNumberJeton) {
                return game.map.grid[x][y];
            }
        }
    }
    return 0;
}

int gameIsWin() {
    const int a = gameIsWinHorizontal();
    const int b = gameIsWinVertical();
    const int c = gameIsWinDiagonal();
    return a+b+c > 0 ? a+b+c : 0;
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
            } else if (event.type == SDL_KEYDOWN && game.playerWin == 0) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    run = 0;
                }
            } else if (event.type == SDL_KEYDOWN && game.playerWin > 0) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    gameReset();
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT && game.playerWin == 0) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= 0 && mouseX < game.window.width && mouseY >= 0 && mouseY < game.window.height) {
                        gameClickEvent(mouseX, mouseY);
                    }
                } else if (event.button.button == SDL_BUTTON_LEFT && game.playerWin > 0) {
                    gameReset();
                }
            }
        }

        // Affichage
        SDL_RenderClear(game.window.renderer);
        graphicDisplayGrid();
        graphicsDisplayJeton();
        graphicDisplayTurn(game.turnPlayer);
        bandeau(game.turnPlayer);

        if (game.playerWin > 0) {
            graphicDisplayWin(game.playerWin);
        }

        SDL_RenderPresent(game.window.renderer);

    }

    gameClose();
}
