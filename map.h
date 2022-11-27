#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "global.h"
#include "load_map.h"

#define SPAWN_RATE 2

void map_generate(int matrix[64][64], int bridges[64][64], Vector2 *vector);
void map_draw(int matrix[64][64], Texture2D sprite, Texture2D sprite_dos);

//Fix textures
#define MUSH_RCORNER 18
#define MUSH_LCORNER 17
#define AMOGUS 16

//Decoration
#define GRASS 15
#define PATH_1 14
#define PATH_2 13
#define PATH_3 12
#define PATH_4 11
#define BMUSH 10
#define RMUSH 9

// Horizontal bridge floors
#define R_FBRIDGE_END 8
#define L_FBRIDGE_END 7
#define H_FBRIDGE 6

// Vertical bridge floors
#define D_FBRIDGE_END 5
#define U_FBRIDGE_END 4
#define V_FBRIDGE 3

//Floors
#define FLOOR_SPAWN 2
#define FLOOR 1

//Walls
#define WALL 0
#define L_WALL (-1)
#define LR_WALL (-2)
#define LU_WALL (-3)
#define LD_WALL (-4)
#define LRU_WALL (-5)
#define LRD_WALL (-6)
#define LRUD_WALL (-7)
#define R_WALL (-8)
#define RU_WALL (-9)
#define RD_WALL (-10)
#define RUD_WALL (-11)
#define U_WALL (-12)
#define UD_WALL (-13)
#define D_WALL (-14)
#define LUD_WALL (-15)

//Horizontal bridge walls
#define R_WBRIDGE_END (-16)
#define L_WBRIDGE_END (-17)
#define H_WBRIDGE (-18)

//Vertical bridge walls
#define LU_WBRIDGE_END (-19)
#define RU_WBRIDGE_END (-20)
#define LD_WBRIDGE_END (-21)
#define RD_WBRIDGE_END (-22)
#define LV_WBRIDGE (-23)
#define RV_WBRIDGE (-24)

//Edges >:(
#define Q_EDGE (-25)
#define Z_EDGE (-26)
#define P_EDGE (-27)
#define M_EDGE (-28)
#define QZ_EDGE (-29)
#define QP_EDGE (-30)
#define QM_EDGE (-31)
#define ZP_EDGE (-32)
#define ZM_EDGE (-33)
#define PM_EDGE (-34)
#define QZP_EDGE (-35)
#define QZM_EDGE (-36)
#define ZPM_EDGE (-37)
#define QPM_EDGE (-38)
#define QZPM_EDGE (-39)

#endif //GAME_MAP_H
