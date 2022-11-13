
#ifndef GAME_JUEGO_H
#define GAME_JUEGO_H

#include "librarby.h"
#include "global.h"


Player* create_player();
void draw_player(Player* a);
void move_player(Player* a);

void chocar_paredes(Player* p, Walls* w);

#endif //GAME_JUEGO_H
