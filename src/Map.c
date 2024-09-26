#include "Map.h"
#include "Game.h"

int mapInit(const int x, const int y) {
    game.map.alloc = 0;
    if (x <= 0 || y <= 0 || x >= MAP_SIZE_X_LIMIT || y >= MAP_SIZE_Y_LIMIT) {
        printf("mapInit Error: invalid map size\n");
        return 1;
    }

    game.map.sizeX = x;
    game.map.sizeY = y;
    game.map.grid = malloc(sizeof(int *) * x);
    for (int i = 0; i < x; i++) {
        game.map.grid[i] = malloc(sizeof(int) * y);
        for (int j = 0; j < y; j++) {
            game.map.grid[i][j] = 0;
        }
    }
    game.map.alloc = 1;
    return 0;
}
void mapClose() {
    if (game.map.alloc) {
        for (int i = 0; i < game.map.sizeX; i++) {
            free(game.map.grid[i]);
        }
        free(game.map.grid);
    }
    game.map.alloc = 0;
}