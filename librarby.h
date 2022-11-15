
#ifndef GAME_LIBRARBY_H
#define GAME_LIBRARBY_H

#include "global.h"

typedef struct list List;

Rectangle create_hitbox(float x, float y);
Walls* crear_paredes();     //Se va a cambiar
void draw_walls(Walls* w);  //Se va a cambiar

#endif //GAME_LIBRARBY_H
