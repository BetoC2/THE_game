#include "map.h"
#include "load_map.h"
#include "global.h"

typedef struct sides{
    int l;
    int r;
    int u;
    int d;
}Sides;

typedef struct edges{
    int lu;
    int ld;
    int ru;
    int rd;
}Edges;

int is_inside(int x,int y){
    if (x < 16 && x >= 0){
        if (y < 16 && y >= 0)
            return 1;
    }
    return 0;
}

int assign_walue(Sides s){
    if (s.l && !s.r && !s.u && !s.d )
        return L_WALL;
    else if (!s.l && s.r && !s.u && !s.d)
        return R_WALL;
    else if (!s.l && !s.r && s.u && !s.d)
        return U_WALL;
    else if (!s.l && !s.r && !s.u && s.d)
        return D_WALL;
    else if (s.l && s.r && !s.u && !s.d)
        return LR_WALL;
    else if (s.l && !s.r && s.u && !s.d)
        return LU_WALL;
    else if (s.l && !s.r && !s.u && s.d)
        return LD_WALL;
    else if (!s.l && s.r && s.u && !s.d)
        return RU_WALL;
    else if (!s.l && s.r && !s.u && s.d)
        return RD_WALL;
    else if (!s.l && !s.r && s.u && s.d)
        return UD_WALL;
    else if (s.l && s.r && s.u && !s.d)
        return LRU_WALL;
    else if (s.l && s.r && !s.u && s.d)
        return LRD_WALL;
    else if (!s.l && s.r && s.u && s.d)
        return RUD_WALL;
    else if (s.l && !s.r && s.u && s.d)
        return LUD_WALL;
    else if (s.l && s.r && s.u && s.d)
        return LRUD_WALL;
    else
        return WALL;
}

int assign_edges(Edges e){
    if (e.lu && !e.ld && !e.ru && !e.rd)
        return Q_EDGE;
    else if (!e.lu && e.ld && !e.ru && !e.rd)
        return Z_EDGE;
    else if (!e.lu && !e.ld && e.ru && !e.rd)
        return P_EDGE;
    else if (!e.lu && !e.ld && !e.ru && e.rd)
        return M_EDGE;
    else if (e.lu && e.ld && !e.ru && !e.rd)
        return QZ_EDGE;
    else if (e.lu && !e.ld && e.ru && !e.rd)
        return QP_EDGE;
    else if (e.lu && !e.ld && !e.ru && e.rd)
        return QM_EDGE;
    else if (!e.lu && e.ld && e.ru && !e.rd)
        return ZP_EDGE;
    else if (!e.lu && e.ld && !e.ru && e.rd)
        return ZM_EDGE;
    else if (!e.lu && !e.ld && e.ru && e.rd)
        return PM_EDGE;
    else if (e.lu && e.ld && e.ru && !e.rd)
        return QZP_EDGE;
    else if (e.lu && e.ld && !e.ru && e.rd)
        return QZM_EDGE;
    else if (!e.lu && e.ld && e.ru && e.rd)
        return ZPM_EDGE;
    else if (e.lu && !e.ld && e.ru && e.rd)
        return QPM_EDGE;
    else if (e.lu && e.ld && e.ru && e.rd)
        return QZPM_EDGE;
    else
        return WALL;
}

void make_map(int map[16][16]){
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++) {
            if (map[i][j] == WALL){
                Sides coords = {0,0,0,0};
                if (is_inside(j+1,i)){
                    if (map[i][j+1] == FLOOR)
                        coords.r = 1;
                }
                if (is_inside(j-1,i)){
                    if (map[i][j-1] == FLOOR)
                        coords.l = 1;
                }
                if (is_inside(j,i-1)){
                    if (map[i-1][j] == FLOOR)
                        coords.u = 1;
                }
                if (is_inside(j,i+1)){
                    if (map[i+1][j] == FLOOR)
                        coords.d = 1;
                }
                map[i][j] = assign_walue(coords);
            }

        }
    }
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++) {
            if (map[i][j] == WALL){
                Edges coords = {0,0,0,0};
                if (is_inside(j-1,i-1)){
                    if (map[i-1][j-1] == FLOOR)
                        coords.lu = 1;
                }
                if (is_inside(j-1,i+1)){
                    if (map[i+1][j-1] == FLOOR)
                        coords.ld = 1;
                }
                if (is_inside(j+1,i-1)){
                    if (map[i-1][j+1] == FLOOR)
                        coords.ru = 1;
                }
                if (is_inside(j+1,i+1)){
                    if (map[i+1][j+1] == FLOOR)
                        coords.rd = 1;
                }
                map[i][j] = assign_edges(coords);
            }
        }
    }
}

void load_raw(int map[16][16], char *name){
    FILE *file = fopen(name,"r");
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++)
            fread(&map[i][j], sizeof(int), 1, file);
    }
    fclose(file);
}

void write_map(int map[16][16], char *name, int index){
    make_map(map);
    if (index == 0){
        map[9][6] = MUSH_LCORNER;
        map[9][9] = MUSH_RCORNER;
    }
    if (index == 5){
        map[12][8] = AMOGUS;
    }
    FILE *file = fopen(name,"w");
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++) {
            fwrite(&map[i][j], sizeof(int), 1, file);
        }
    }
    fclose(file);
}

void load_maps(void) {
    char raws[8][20] = {
            {"../maps/raws/raw_1"},
            {"../maps/raws/raw_2"},
            {"../maps/raws/raw_3"},
            {"../maps/raws/raw_4"},
            {"../maps/raws/raw_5"},
            {"../maps/raws/raw_6"},
            {"../maps/raws/raw_7"},
            {"../maps/raws/raw_s"}
    };
    char maps[8][14] = {
            {"../maps/map_1"},
            {"../maps/map_2"},
            {"../maps/map_3"},
            {"../maps/map_4"},
            {"../maps/map_5"},
            {"../maps/map_6"},
            {"../maps/map_7"},
            {"../maps/map_s"}
    };

    for (int i = 0; i < 8; i++){
        int map[16][16];
        load_raw(map, raws[i]);
        write_map(map, maps[i], i);
    }
}
