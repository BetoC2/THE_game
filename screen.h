#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "global.h"
#include "map.h"

int screen_update(int map[64][64], int bridges[64][64], int *water_temp, Camera2D camara,
                   Font fuente, Texture2D sprite_w, Texture2D sprite_d, Texture2D sprite_decor);

int screen_title(int map[64][64], int bridges[64][64], int *water_temp, Camera2D camara,
                 Font fuente, Texture2D sprite_w, Texture2D sprite_d, Texture2D sprite_decor);

int screen_pause(int map[64][64], int bridges[64][64], int *water_temp, Camera2D camara,
                 Font fuente, Texture2D sprite_w, Texture2D sprite_d, Texture2D sprite_decor);

int screen_gameover(Camera2D camara, Font fuente);

#endif //GAME_SCREEN_H
