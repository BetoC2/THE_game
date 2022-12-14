
#ifndef GAME_JUEGO_H
#define GAME_JUEGO_H

#include "global.h"

// AWAS
List* spawn_awas(Vector2* v);
void draw_awa(List* l, Texture2D spr);
void manage_awa(List* l, Player* p);

// JUGADOR
Player* create_player(Vector2* v);
void draw_player(Player* p,Texture2D sprite, Texture2D hit, Texture2D sprite_r);
int manage_player(Player* p);

//PAREDES
List* crate_walls(int map[64][64]);
void chocar_paredes(Player* p, List* w);

//ENEMIGOS
List* summon_enemies(int map[64][64]);
void draw_enemies(List* l, Texture2D sprite);
int manage_enemies(Player* p, List* l, List* a);

//Cámara
Camera2D crear_camara(Player* p);
void update_camara(Player* p, Camera2D* c);

//Cosos
void draw_stats(Player* p, Texture2D spr, Camera2D c);
void matar_todo(Player* p, List* l_2, List* l_3, List* l_4);

#endif //GAME_JUEGO_H
