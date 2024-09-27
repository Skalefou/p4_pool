
#include "Game.h"
#include "SDL_image.h"

Game game;

int gameInit() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }
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
    game.playerWin = 0;
    return 0;
}

void gameClose() {
    //Mix_CloseAudio();
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
            game.playerWin = gameIsWin();
        }
    }
}

int gameIsWinHorizontal() {
    for (int x = 0; x < game.map.sizeX; x++) {
        for(int i = 0; i < game.map.sizeY-3; i++) {
            if (game.map.grid[x][i] != 0 && game.map.grid[x][i] == game.map.grid[x][i+1] && game.map.grid[x][i] == game.map.grid[x][i+2] && game.map.grid[x][i] == game.map.grid[x][i+3]) {
                return game.map.grid[x][i];
            }
        }
    }
    return 0;
}

int gameIsWinVertical() {
    for (int y = 0; y < game.map.sizeY; y++) {
        for(int i = 0; i < game.map.sizeX-3; i++) {
            if (game.map.grid[i][y] != 0 && game.map.grid[i][y] == game.map.grid[i+1][y] && game.map.grid[i][y] == game.map.grid[i+2][y] && game.map.grid[i][y] == game.map.grid[i+3][y]) {
                return game.map.grid[i][y];
            }
        }
    }
    return 0;
}

int gameIsWinDiagonal() {
    for (int x = 0; x < game.map.sizeX-3; x++) {
        for (int y = 0; y < game.map.sizeY-3; y++) {
            if (game.map.grid[x][y] != 0 && game.map.grid[x][y] == game.map.grid[x+1][y+1] && game.map.grid[x][y] == game.map.grid[x+2][y+2] && game.map.grid[x][y] == game.map.grid[x+3][y+3]) {
                return game.map.grid[x][y];
            }
        }
    }
    for (int x = 0; x < game.map.sizeX-3; x++) {
        for (int y = 3; y < game.map.sizeY; y++) {
            if (game.map.grid[x][y] != 0 && game.map.grid[x][y] == game.map.grid[x+1][y-1] && game.map.grid[x][y] == game.map.grid[x+2][y-2] && game.map.grid[x][y] == game.map.grid[x+3][y-3]) {
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

int gameGo() {
    SDL_Surface *image = IMG_Load("./resource/go.png");
    if (!image) {
        printf("Failed to load image! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(game.window.renderer, image);
    SDL_FreeSurface(image);
    if (!texture) {
        printf("Failed to create texture! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Rect rect = {0, 0, image->w / 2, image->h / 2};
    double angle = 0.0;
    int run = 1;

    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = 0;
            } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_i) {
                run = 0;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_I]) {
            angle += 0.1;
        }

        SDL_RenderClear(game.window.renderer);
        SDL_RenderCopyEx(game.window.renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(game.window.renderer);
    }

    SDL_DestroyTexture(texture);
    return 0;
}

void gameRuntime() {
    if (gameInit()) {
        gameClose();
        return;
    }

    Mix_Music *bgMusic = Mix_LoadMUS("./resource/musique.mp3");
    if (!bgMusic) {
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(bgMusic, -1); // Play music indefinitely
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
                } else if (event.key.keysym.sym == SDLK_g) {
                    gameGo();
                }
            } else if (event.type == SDL_KEYDOWN && game.playerWin > 0) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    gameClose();
                    gameInit();
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT && game.playerWin == 0) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= 0 && mouseX < game.window.width && mouseY >= 0 && mouseY < game.window.height) {
                        gameClickEvent(mouseX, mouseY);
                    }
                } else if (event.button.button == SDL_BUTTON_LEFT && game.playerWin > 0) {
                    gameClose();
                    gameInit();
                }
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_I]) {
            gameGo();
        }

        // Affichage
        SDL_RenderClear(game.window.renderer);
        graphicDisplayGrid();
        graphicsDisplayJeton();
        bandeau();

        if (game.playerWin > 0) {
            graphicDisplayWin(game.playerWin);
        }

        SDL_RenderPresent(game.window.renderer);
    }

    Mix_FreeMusic(bgMusic);
    gameClose();
}
