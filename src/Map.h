#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include "Game.h"

#define MAP_SIZE_X_LIMIT 20
#define MAP_SIZE_Y_LIMIT 20

int mapInit(const int x, const int y);
void mapClose();

typedef struct {
    int **grid;
    int sizeX, sizeY, alloc;
} Map;

#endif