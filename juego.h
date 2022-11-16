
#ifndef GAME_JUEGO_H
#define GAME_JUEGO_H

#include "librarby.h"
#include "global.h"

// JUGADOR
Player* create_player();
void draw_player(Player* a);
void move_player(Player* a);

//PAREDES
List* crate_walls();
void draw_walls(List* l);
void chocar_paredes(Player* p, List* w);

#endif //GAME_JUEGO_H
