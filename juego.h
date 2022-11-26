
#ifndef GAME_JUEGO_H
#define GAME_JUEGO_H

#include "global.h"

// AWAS
List* spawn_awas(Vector2* v);
void draw_awa(List* l);
void manage_awa(List* l, Player* p);

// JUGADOR
Player* create_player(Vector2* v);
void draw_player(Player* p);
int manage_player(Player* p);

//PAREDES
List* crate_walls(int map[64][64]);
void draw_walls(List* l);
void chocar_paredes(Player* p, List* w);

//ENEMIGOS
List* summon_enemies(int map[64][64]);
void draw_enemies(List* l);
void manage_enemies(Player* p, List* l, List* a);

#endif //GAME_JUEGO_H
