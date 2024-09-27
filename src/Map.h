#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

#define MAP_SIZE_X_LIMIT 20
#define MAP_SIZE_Y_LIMIT 20

int mapInit(const int x, const int y);
int isLimitColumn(const int column);
void setJeton(const int player, const int column);
void mapClose();
void mapReset();

typedef struct {
    int **grid;
    int sizeX, sizeY, alloc;
} Map;

#endif