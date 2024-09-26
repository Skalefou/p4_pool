#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>

int graphicInit();
void graphicClose();
void graphicDisplayGrid();

typedef struct {
  int spriteNb;
  SDL_Texture *sprite[2];
 } Graphic;

#endif