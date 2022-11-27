#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "global.h"
#include "load_map.h"

#define SPAWN_RATE 2

void map_generate(int matrix[64][64], int bridges[64][64], Vector2 *vector);
void map_draw(int matrix[64][64], Texture2D sprite, Texture2D sprite_dos);

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

//Fix textures
#define MUSH_RCORNER (-16)
#define MUSH_LCORNER (-17)
#define AMOGUS (-18)
#define AMOGUS2 (-19)
#define AMOGUS3 (-20)
#define AMOGUS4 (-21)

//Horizontal bridge walls
#define R_WBRIDGE_END (-22)
#define L_WBRIDGE_END (-23)
#define H_WBRIDGE (-24)
#define L_WEND (-25)
#define H_DFLOOR (-26)
#define R_WEND (-27)

//Vertical bridge walls
#define LU_WBRIDGE_END (-28)
#define RU_WBRIDGE_END (-29)
#define LD_WBRIDGE_END (-30)
#define RD_WBRIDGE_END (-31)
#define LV_WBRIDGE (-32)
#define RV_WBRIDGE (-33)

//Edges >:(
#define Q_EDGE (-34)
#define Z_EDGE (-35)
#define P_EDGE (-36)
#define M_EDGE (-37)
#define QZ_EDGE (-38)
#define QP_EDGE (-39)
#define QM_EDGE (-40)
#define ZP_EDGE (-41)
#define ZM_EDGE (-42)
#define PM_EDGE (-43)
#define QZP_EDGE (-44)
#define QZM_EDGE (-45)
#define ZPM_EDGE (-46)
#define QPM_EDGE (-47)
#define QZPM_EDGE (-48)

#endif //GAME_MAP_H
