#ifndef CONFIG_H
#define CONFIG_H

int configInit();
void configClose();

enum {
    MODE_LOCAL = 0,
    MODE_SERVER = 1,
    MODE_CLIENT = 2
};

typedef struct {
    // Jeu
    int rows;
    int columns;
    int winNumberJeton;
    int playerNb;

    // Reseau
    int modeOnline;
    char *ip;
    int ipLen;
    int port;
} Config;

#endif