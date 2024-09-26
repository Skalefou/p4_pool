#include "Game.h"
#include "Graphic.h"
#include <SDL2/SDL_image.h>

int graphicInit() {
    if (graphicInitSprites()) {
        return 1;
    }

    if (graphicInitTextTurn()) {
        return 1;
    }

    if (graphicInitTextWin()) {
        return 1;
    }

    return 0;
}

int graphicInitSprites() {
    const char *spritePaths[] = {
        "./resource/player1.png",
        "./resource/player2.png"
    };

    game.graphic.spriteNb = 2;
    for (int i = 0; i < game.graphic.spriteNb; i++) {
        SDL_Surface *surface = IMG_Load(spritePaths[i]);
        if (!surface) {
            printf("IMG_Load Error: %s\n", IMG_GetError());
            return 1;
        }

        game.graphic.sprite[i] = SDL_CreateTextureFromSurface(game.window.renderer, surface);
        SDL_FreeSurface(surface);

        if (!game.graphic.sprite[i]) {
            printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
            return 1;
        }
    }
    return 0;
}

int graphicInitTextTurn() {
    const SDL_Color colorText = {232, 252, 252, 255};
    const char *textTurn[] = {
        "Au tours du joueur 1 !",
        "Au tours du joueur 2 !"
    };

    game.graphic.font = TTF_OpenFont("./resource/font.ttf", 24);
    if (!game.graphic.font) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        return 1;
    }

    for (int i = 0; i < 2; i++) {
        SDL_Surface *surface = TTF_RenderText_Solid(game.graphic.font, textTurn[i], colorText);
        if (!surface) {
            printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
            return 1;
        }
        game.graphic.textTurn[i] = SDL_CreateTextureFromSurface(game.window.renderer, surface);
        SDL_FreeSurface(surface);
        if (!game.graphic.textTurn[i]) {
            printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
            return 1;
        }
        SDL_QueryTexture(game.graphic.textTurn[i], NULL, NULL, &game.graphic.textTurnPos[i].w, &game.graphic.textTurnPos[i].h);
    }
    game.graphic.textTurnNb = 2;
    return 0;
}

int graphicInitTextWin() {
    SDL_Color colorText = {255, 255, 0, 255};
    char *textWin[] = {
        "Le joueur 1 a gagne !",
        "Le joueur 2 a gagne !"
    };

    for (int i = 0; i < 2; i++) {
        SDL_Surface *surface = TTF_RenderText_Solid(game.graphic.font, textWin[i], colorText);
        if (!surface) {
            printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
            return 1;
        }
        game.graphic.textWin[i] = SDL_CreateTextureFromSurface(game.window.renderer, surface);
        SDL_FreeSurface(surface);
        if (!game.graphic.textWin[i]) {
            printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
            return 1;
        }
        SDL_QueryTexture(game.graphic.textWin[i], NULL, NULL, &game.graphic.textWinPos[i].w, &game.graphic.textWinPos[i].h);
        game.graphic.textWinPos[i].x = (game.window.width - game.graphic.textWinPos[i].w) / 2;
        game.graphic.textWinPos[i].y = (game.window.height - game.graphic.textWinPos[i].h) / 2;
    }
    game.graphic.textWinNb = 2;
    return 0;
}

void graphicDisplayGrid() {
    SDL_SetRenderDrawColor(game.window.renderer, 255, 255, 255, 255);
    for (int x = 0; x < game.window.width; x += 64) {
        SDL_RenderDrawLine(game.window.renderer, x, 0, x, game.window.height);
    }
    for (int y = 0; y < game.window.height; y += 64) {
        SDL_RenderDrawLine(game.window.renderer, 0, y, game.window.width, y);
    }
    SDL_SetRenderDrawColor(game.window.renderer, 0, 0, 0, 255);
}

void graphicDisplayTurn(const int turn) {
    SDL_Rect rect = {0, 0, 0, 0};
    rect.w = game.graphic.textTurnPos[turn].w;
    rect.h = game.graphic.textTurnPos[turn].h;
    SDL_RenderCopy(game.window.renderer, game.graphic.textTurn[turn], NULL, &rect);
}

void graphicDisplayWin(const int player) {
    SDL_RenderCopy(game.window.renderer, game.graphic.textWin[player-1], NULL, &game.graphic.textWinPos[player-1]);
}

void graphicsDisplayJeton() {
    for (int x = 0; x < game.map.sizeX; x++) {
        for (int y = 0; y < game.map.sizeY; y++) {
            if (game.map.grid[x][y] != 0) {
                SDL_Rect rect = {x * 64, y * 64, 64, 64};
                SDL_RenderCopy(game.window.renderer, game.graphic.sprite[game.map.grid[x][y] - 1], NULL, &rect);
            }
        }
    }
}

void graphicCloseSprites() {
    for (int i = 0; i < game.graphic.spriteNb; i++) {
        if (game.graphic.sprite[i] != NULL) {
            SDL_DestroyTexture(game.graphic.sprite[i]);
        }
    }
}

void graphicCloseTextTurn() {
    for (int i = 0; i < 2; i++) {
        if (game.graphic.textTurn[i] != NULL) {
            SDL_DestroyTexture(game.graphic.textTurn[i]);
        }
    }

}

void graphicCloseTextWin() {
    for (int i = 0; i < game.graphic.textWinNb; i++) {
        if (game.graphic.textWin[i] != NULL) {
            SDL_DestroyTexture(game.graphic.textWin[i]);
        }
    }
}

void graphicClose() {
    graphicCloseTextWin();
    graphicCloseTextTurn();

    if (game.graphic.font != NULL) {
        TTF_CloseFont(game.graphic.font);
    }

    graphicCloseSprites();
}

void bandeau() {
    int tailleTxtCentre = 200;
    int debutTxtCentre = SCREEN_WIDTH_DEFAULT / 2-tailleTxtCentre/2;
    SDL_Rect rectBandeau = {0, SCREEN_HEIGHT_DEFAULT - 40, SCREEN_WIDTH_DEFAULT, 40};
    SDL_Rect rectTextTurn = {debutTxtCentre, SCREEN_HEIGHT_DEFAULT+5 - 40, tailleTxtCentre, 30};
    SDL_SetRenderDrawColor(game.window.renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(game.window.renderer, &rectBandeau);
    SDL_RenderCopy(game.window.renderer, game.graphic.textTurn[0], NULL, &rectTextTurn);
    SDL_SetRenderDrawColor(game.window.renderer, 0, 0, 0, 255);
}
