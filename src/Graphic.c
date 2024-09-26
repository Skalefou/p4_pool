#include "Game.h"
#include "Graphic.h"
#include <SDL2/SDL_image.h>

int graphicInit() {
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

void graphicClose() {
    for (int i = 0; i < game.graphic.spriteNb; i++) {
        if (game.graphic.sprite[i] != NULL) {
            SDL_DestroyTexture(game.graphic.sprite[i]);
        }
    }
}