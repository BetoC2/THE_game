
#ifndef GAME_GLOBAL_H
#define GAME_GLOBAL_H

//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raylib.h"

//Constantes
#define S_WIDHT 1024
#define S_HEIGHT 640
#define SIZE 16
#define FPS 60
#define TILE SIZE
#define WATER (Color){ 92, 105, 159, 255 }

//Estructuras existentes
typedef struct player Player;
typedef struct enemy Enemy;
typedef struct wall Wall;
typedef struct floor Floor;
typedef struct awas AwasdeSabor;

typedef struct list List;


#endif //GAME_GLOBAL_H
