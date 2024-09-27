#include "Config.h"
#include "Game.h"
#include <stdio.h>

int configInit() {
    FILE *file = fopen("config.txt", "r");
    if (file == NULL) {
        printf("Fichier introuvable\n");
        return 1;
    }

    char line[256];
    game.config.ip = malloc(256);
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "ROWS=%d", &game.config.rows) == 1) continue;
        if (sscanf(line, "COLS=%d", &game.config.columns) == 1) continue;
        if (sscanf(line, "WIN=%d", &game.config.winNumberJeton) == 1) continue;
        if (sscanf(line, "JOUEUR=%d", &game.config.playerNb) == 1) continue;
        if (sscanf(line, "MODE=%d", &game.config.modeOnline) == 1) continue;
        if (sscanf(line, "IP=%ms", &game.config.ip) == 1) continue;
        if (sscanf(line, "PORT=%d", &game.config.port) == 1) continue;
    }

    if (game.config.winNumberJeton <= 1) {
        printf("Il faut un nombre de jeton");
        return 1;
    }

    if (game.config.rows < 4 || game.config.columns < 4 || (game.config.columns < game.config.winNumberJeton && game.config.rows < game.config.winNumberJeton)) {
        printf("La taille minimum est 4x4 et une des lignes/colonnes doit au moins etre superieur au nombre de victoire avec jeton\n");
        return 1;
    }

    if (game.config.playerNb <= 1) {
        printf("Il faut au moins deux joueurs !\n");
        return 1;
    }

    fclose(file);
    return 0;
}

void configClose() {
    free(game.config.ip);
}