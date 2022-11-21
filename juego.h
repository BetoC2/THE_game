
#ifndef GAME_JUEGO_H
#define GAME_JUEGO_H

#include "global.h"

// JUGADOR
Player* create_player();
void draw_player(Player* p);
void manage_player(Player* p);

//PAREDES
List* crate_walls();
void draw_walls(List* l);
void chocar_paredes(Player* p, List* w);

//ENEMIGOS
List* summon_enemies();
void draw_enemies(List* l);
void manage_enemies(Player* p, List* l);

#endif //GAME_JUEGO_H
