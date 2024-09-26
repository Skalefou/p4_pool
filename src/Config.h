#ifndef CONFIG_H
#define CONFIG_H

enum {
    MODE_LOCAL = 0,
    MODE_SERVER = 1,
    MODE_CLIENT = 2
};

typedef struct {
    int rows;
    int columns;
    int winNumberJeton;

    int modeOnline;
    char *ip;
    int port;
} Config;

#endif