
#ifndef GAME_GLOBAL_H
#define GAME_GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define S_WIDHT 1024
#define S_HEIGHT 640
#define SIZE 64

typedef struct player Player;
typedef struct enemy Enemy;
typedef struct wall Wall;

typedef struct walls{ //SE VA A ELIMINAR
    Rectangle* array;
    int size;
}Walls;

#endif //GAME_GLOBAL_H
