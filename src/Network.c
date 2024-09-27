#include "Network.h"
#include "Game.h"
#include <stdlib.h>
#include "cJSON.h"

cJSON *encryptToJson() {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "sizeX", game.map.sizeX);
    cJSON_AddNumberToObject(json, "sizeY", game.map.sizeY);
    cJSON_AddNumberToObject(json, "playerWin", game.playerWin);
    cJSON_AddNumberToObject(json, "turnPlayer", game.turnPlayer);
    cJSON *tileMap = cJSON_CreateArray();
    for (int i = 0; i < game.map.sizeX; i++) {
        cJSON *rowArray = cJSON_CreateIntArray((const int *)game.map.grid[i], game.map.sizeY);
        cJSON_AddItemToArray(tileMap, rowArray);
    }
    cJSON_AddItemToObject(json, "grid", tileMap);
    return json;
}

void decryptJson(char *jsonStr) {
    cJSON *json = cJSON_Parse(jsonStr);

    cJSON *sizeX = cJSON_GetObjectItem(json, "sizeX");
    cJSON *sizeY = cJSON_GetObjectItem(json, "sizeY");
    cJSON *playerWin = cJSON_GetObjectItem(json, "playerWin");
    cJSON *turnPlayer = cJSON_GetObjectItem(json, "turnPlayer");
    cJSON *grid = cJSON_GetObjectItem(json, "grid");

    mapClose();
    game.map.sizeX = sizeX->valueint;
    game.map.sizeY = sizeY->valueint;
    game.playerWin = playerWin->valueint;
    game.turnPlayer = turnPlayer->valueint;

    game.map.grid = malloc(sizeof(int *) * game.map.sizeX);
    for(int i = 0; i < game.map.sizeX; i++) {
        game.map.grid[i] = malloc(sizeof(int) * game.map.sizeY);
    }

    for (int i = 0; i < game.map.sizeX; i++) {
        cJSON *row = cJSON_GetArrayItem(grid, i);
        for (int j = 0; j < game.map.sizeY; j++) {
            game.map.grid[i][j] = cJSON_GetArrayItem(row, j)->valueint;
        }
    }

    cJSON_Delete(json);
}


int networkInitServeur() {
    if (SDLNet_ResolveHost(&game.network.ip, NULL, game.config.port) == -1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return 1;
    }

    game.network.serveur = SDLNet_TCP_Open(&game.network.ip);
    if (!game.network.serveur) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        return 1;
    }

    printf("Serveur ouvert au port %d\n", game.config.port);
    game.network.nbClientsConnect = 0;
    return 0;
}

int networkInitClient() {
    if (SDLNet_ResolveHost(&game.network.ip, game.config.ip, game.config.port) == -1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return 1;
    }

    game.network.serveur = SDLNet_TCP_Open(&game.network.ip);
    if (!game.network.serveur) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        return 1;
    }

    printf("Connecte au %s et port : %d\n", game.config.ip, game.config.port);

    return 0;
}

void networkServeurRuntime() {
    TCPsocket client = SDLNet_TCP_Accept(game.network.serveur);
    if (client) {
        if (game.network.nbClientsConnect < 5) {
            game.network.clients[game.network.nbClientsConnect] = client;
            game.network.nbClientsConnect++;
        } else {
            SDLNet_TCP_Close(client);
        }
    }
}

void networkServerSendData() {
    cJSON *json = encryptToJson();
    char *jsonStr = cJSON_Print(json);
    int jsonStrLen = strlen(jsonStr) + 1;

    for (int i = 0; i < game.network.nbClientsConnect; i++) {
        if (SDLNet_TCP_Send(game.network.clients[i], jsonStr, jsonStrLen) < jsonStrLen) {
            printf("Erreur echange de donnee : %s\n", SDLNet_GetError());
        }
    }

    cJSON_Delete(json);
    free(jsonStr);
}

void networkClientReceiveData() {
    char buffer[1024];
    int data = SDLNet_TCP_Recv(game.network.serveur, buffer, 1024);
    if (data > 0) {
        buffer[data] = '\0';
        decryptJson(buffer);

    }
}

void networkCloseServeur() {
    SDLNet_TCP_Close(game.network.serveur);
}