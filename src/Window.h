#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH_DEFAULT 448
#define SCREEN_HEIGHT_DEFAULT 424
#define HEIGHT_BANDEAU 40

int windowInit(const int rows, const int columns);
void windowClose();

typedef struct  {
    int width;
    int height;
    SDL_Window *screen;
    SDL_Renderer *renderer;
} Window;

#endif
