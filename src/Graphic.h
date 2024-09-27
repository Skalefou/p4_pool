#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int graphicInit();
int graphicInitSprites();
int graphicInitTextTurn();
int graphicInitTextWin();

void graphicsDisplayJeton();
void graphicDisplayGrid();
void graphicDisplayTurn(const int turn);
void bandeau();
void graphicDisplayWin(const int player);

void graphicClose();
void graphicCloseSprites();
void graphicCloseTextTurn();
void graphicCloseTextWin();


typedef struct {
    // Sprites
    int spriteNb;
    SDL_Texture *sprite[5];

    // Textes
    TTF_Font *font;
    SDL_Texture *textTurn[5];
    SDL_Rect textTurnPos[5];
    int textTurnNb;

    SDL_Rect textWinPos[5];
    SDL_Texture *textWin[5];
    int textWinNb;

 } Graphic;

#endif
