#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int graphicInit();
void graphicClose();
void graphicDisplayGrid();
void graphicDisplayTurn(const int turn);

typedef struct {
    // Sprites
    int spriteNb;
    SDL_Texture *sprite[2];

    // Textes
    TTF_Font *font;
    SDL_Texture *textTurn[2];
    SDL_Rect textTurnPos[2];
    int textTurnNb;
 } Graphic;

#endif