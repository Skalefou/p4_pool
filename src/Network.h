#ifndef NETWORK_H
#define NETWORK_H

#include <SDL2/SDL_net.h>
#include "cJSON.h"

cJSON *encryptToJson();
int networkInitServeur();
int networkInitClient();
void networkServeurRuntime();
void networkCloseServeur();
void networkServerSendData();
void networkClientReceiveData();

typedef struct {
    int sizeX;
    int sizeY;
    int playerWin;
    int turnPlayer;
    int **grid;
} DTO;

typedef struct {
    IPaddress ip;
    TCPsocket serveur;
    TCPsocket clients[5];
    int nbClientsConnect;
} Network;

#endif //NETWORK_H
