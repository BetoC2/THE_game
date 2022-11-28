#include "map.h"

//FUNCIONES DE APOYO
void copy_matrix(int matrix[64][64], int to_copy[64][64]){
    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++){
            to_copy[i][j] = matrix[i][j];
        }
    }
}

int room_is_inside(int x, int y){
    if (x < 4 && x >= 0){
        if (y < 4 && y >= 0)
            return 1;
    }
    return 0;
}

void rooms_fill(int rooms[4][4], int x, int y, int rep){
    while(rep) {

        if (rooms[x][y] != 1){
            rep--;
            rooms[x][y] = 1;
        }

        short random = rand() % 4;
        switch (random) {
            case 0:
                if(room_is_inside(x-1, y))
                    x--;
                break;

            case 1:
                if(room_is_inside(x+1, y))
                    x++;
                break;

            case 2:
                if(room_is_inside(x, y-1))
                    y--;
                break;
            case 3:
                if(room_is_inside(x, y+1))
                    y++;
                break;
        }
    }
}

void rooms_generate(int rooms[4][4]){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            rooms[i][j] = 0;
        }
    }

    int x = rand() % 4;
    int y = rand() % 4;
    int rep = rand() % 3;
    rooms_fill(rooms, x, y, 7+rep);
}

void rooms_load(int map[16][16], char *name){
    FILE *file = fopen(name,"r");
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++)
            fread(&map[i][j], sizeof(int), 1, file);
    }
    fclose(file);
}

void rooms_get_spawn(int map[16][16]){
    int first_try = 0;
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++){
            if (map[i][j] == FLOOR){
                if (!first_try) {
                    map[i][j] = FLOOR_SPAWN;
                    first_try = 1;
                }
                else{
                    int random = rand() % 100;
                    if (random < SPAWN_RATE)
                        map[i][j] = FLOOR_SPAWN;
                }
            }
        }
    }
}

void rooms_replace(int matrix[64][64], int x, int y, char *name, int spawn_floor){
    int map[16][16];
    rooms_load(map, name);

    if (spawn_floor)
        rooms_get_spawn(map);

    for (int i = y, b = 0; (i < y + TILE) && b < 16; i++,b++){
        for(int j = x, a = 0; (j < x + TILE) && a < 16; j++, a++){
            matrix[i][j] = map[b][a];
        }
    }
}

void rooms_insert(int matrix[64][64], int rooms[4][4], Vector2 *vector){
    char files[8][14] = {
            {"../maps/map_1"},
            {"../maps/map_2"},
            {"../maps/map_3"},
            {"../maps/map_4"},
            {"../maps/map_5"},
            {"../maps/map_6"},
            {"../maps/map_7"},
            {"../maps/map_s"}
    };
    FILE *file = fopen(files[0], "r");
    if (!file){
        fclose(file);
        load_maps();
    }
    else
        fclose(file);

    int first = 0;

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (rooms[i][j] == 1){
                int x = j * TILE;
                int y = i * TILE;
                if (!first){
                    rooms_replace(matrix, x, y, files[7], 0);
                    vector->x = x + 4;
                    vector->y = y + 7;
                    first++;
                }
                else {
                    int random = rand() % 7;
                    rooms_replace(matrix, x, y, files[random], 1);
                }
            }
        }
    }
}

void rooms_connect_right(int matrix[64][64], int x, int y){
    int x_start = x + 15;
    int x_final = x_start;
    int y_index = y + 7;

    while (matrix[y_index][x_start-1] < FLOOR)
        x_start--;

    while (matrix[y_index][x_final+1] < FLOOR)
        x_final++;

    matrix[y_index-1][x_start] = L_WBRIDGE_END;
    matrix[y_index][x_start] = L_FBRIDGE_END;
    matrix[y_index+1][x_start] = L_FBRIDGE_END;
    matrix[y_index+2][x_start] =  L_WEND;
    x_start++;

    while (x_start < x_final){
        matrix[y_index-1][x_start] = H_WBRIDGE;
        matrix[y_index][x_start] = H_FBRIDGE;
        matrix[y_index+1][x_start] = H_FBRIDGE;
        matrix[y_index+2][x_start] =  H_DFLOOR;
        x_start++;
    }

    matrix[y_index-1][x_start] = R_WBRIDGE_END;
    matrix[y_index][x_start] = R_FBRIDGE_END;
    matrix[y_index+1][x_start] = R_FBRIDGE_END;
    matrix[y_index+2][x_start] =  R_WEND;
}

void rooms_connect_down(int matrix[64][64], int x, int y){
    int y_start = y + 15;
    int y_final = y_start;
    int x_index = x + 7;

    while (matrix[y_start-1][x_index] < FLOOR)
        y_start--;

    while (matrix[y_final+1][x_index] < FLOOR)
        y_final++;

    matrix[y_start][x_index-1] = LU_WBRIDGE_END;
    matrix[y_start][x_index] = U_FBRIDGE_END;
    matrix[y_start][x_index+1] = U_FBRIDGE_END;
    matrix[y_start][x_index+2] = RU_WBRIDGE_END;
    y_start++;

    while(y_start < y_final){
        matrix[y_start][x_index-1] = LV_WBRIDGE;
        matrix[y_start][x_index] = V_FBRIDGE;
        matrix[y_start][x_index+1] = V_FBRIDGE;
        matrix[y_start][x_index+2] = RV_WBRIDGE;
        y_start++;
    }
    matrix[y_start][x_index-1] = LD_WBRIDGE_END;
    matrix[y_start][x_index] = V_FBRIDGE;
    matrix[y_start][x_index+1] = V_FBRIDGE;
    matrix[y_start][x_index+2] = RD_WBRIDGE_END;

    y_start++;

    matrix[y_start][x_index] = D_FBRIDGE_END;
    matrix[y_start][x_index+1] = D_FBRIDGE_END;
}

void rooms_insert_decoration(int matrix[64][64]){
    short path;
    short paths[] = {PATH_1,PATH_2,PATH_3,PATH_4};
    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++) {
            int prob = rand() % 100;
            if (prob < 12 && (matrix[i][j] == FLOOR || matrix[i][j] == FLOOR_SPAWN)) {
                short random = rand() % 4;
                switch (random) {
                    case 0:
                        matrix[i][j] = GRASS;
                        break;
                    case 1:
                        matrix[i][j] = BMUSH;
                        break;
                    case 2:
                        matrix[i][j] = RMUSH;
                        break;
                    case 3:
                        path = rand() % 4;
                        matrix[i][j] = paths[path];
                        break;
                }
            }
        }
    }
}

//FUNCIONES PRINCIPALES

void map_generate(int matrix[64][64], int bridges[64][64], Vector2 *vector){
    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++){
            matrix[i][j] = 0;
        }
    }

    int rooms[4][4];
    rooms_generate(rooms);
    rooms_insert(matrix, rooms, vector);
    copy_matrix(matrix, bridges);

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (rooms[i][j]){
                if(room_is_inside(j+1,i)){
                    if (rooms[i][j+1])
                        rooms_connect_right(bridges, j * TILE, i * TILE);
                }
                if(room_is_inside(j, i+1)){
                    if (rooms[i+1][j])
                        rooms_connect_down(bridges, j * TILE, i * TILE);
                }
            }
        }
    }
    rooms_insert_decoration(bridges);
}

void create_texture_wall(Texture2D sprite, int x, int y, Vector2 victor){
    Texture2D spr = sprite;
    Rectangle recto = {x * TILE, y * TILE, (float)spr.width / 15, (float)spr.height / 36};
    DrawTextureRec(spr, recto, victor, WHITE);
}

void create_texture_bridge(Texture2D sprite, int x, int y, Vector2 victor){
    Texture2D spr = sprite;
    Rectangle recto = {x * TILE, y * TILE, (float)spr.width / 25, (float)spr.height / 22};
    DrawTextureRec(spr, recto, victor, WHITE);
}

void create_texture_decor(Texture2D sprite, int x, int y, Vector2 victor){
    Texture2D spr = sprite;
    Rectangle recto = {x * TILE, y * TILE, (float)spr.width / 10, (float)spr.height / 10};
    DrawTextureRec(spr, recto, victor, WHITE);
}

void map_draw(int matrix[64][64], Texture2D sprite, int *temp){
    Vector2 victor;
    int h = (*temp / 30) * 7;
    (*temp)++;
    *temp = *temp == 120 ? 0: *temp;
    
    for (int y = 0; y < 64; y++){
        for (int x = 0; x < 64; x++){
            victor = (Vector2){x * TILE,y * TILE};
            switch (matrix[y][x]) {
                case FLOOR:
                case FLOOR_SPAWN:
                    create_texture_wall(sprite, 2, 30, victor);
                    break;

                case L_WALL:
                    create_texture_wall(sprite, 1, 2 + h, victor);
                    break;
                case LR_WALL:
                    create_texture_wall(sprite, 4, 2 + h, victor);
                    break;
                case LU_WALL:
                    create_texture_wall(sprite, 1, 1 + h, victor);
                    break;
                case LD_WALL:
                    create_texture_wall(sprite, 1, 3 + h, victor);
                    break;
                case LRU_WALL:
                    create_texture_wall(sprite, 4, 1 + h, victor);
                    break;
                case LRD_WALL:
                    create_texture_wall(sprite, 4, 3 + h, victor);
                    break;
                case LRUD_WALL:
                    create_texture_wall(sprite, 4, 4 + h, victor);
                    break;
                case R_WALL:
                    create_texture_wall(sprite, 3, 2 + h, victor);
                    break;
                case RU_WALL:
                    create_texture_wall(sprite, 3, 1 + h, victor);
                    break;
                case RD_WALL:
                    create_texture_wall(sprite, 3, 3 + h, victor);
                    break;
                case RUD_WALL:
                    create_texture_wall(sprite, 3, 4 + h, victor);
                    break;
                case U_WALL:
                    create_texture_wall(sprite, 2, 1 + h, victor);
                    break;
                case UD_WALL:
                    create_texture_wall(sprite, 2, 4 + h, victor);
                    break;
                case D_WALL:
                    create_texture_wall(sprite, 2, 3 + h, victor);
                    break;
                case LUD_WALL:
                    create_texture_wall(sprite, 1, 4 + h, victor);
                    break;

                case Q_EDGE:
                    create_texture_wall(sprite, 6, 2 + h, victor);
                    break;
                case Z_EDGE:
                    create_texture_wall(sprite, 6, 1 + h, victor);
                    break;
                case P_EDGE:
                    create_texture_wall(sprite, 5, 2 + h, victor);
                    break;
                case M_EDGE:
                    create_texture_wall(sprite, 5, 1 + h, victor);
                    break;
                case QZ_EDGE:
                    create_texture_wall(sprite, 7, 2 + h, victor);
                    break;
                case QP_EDGE:
                    create_texture_wall(sprite, 6, 4 + h, victor);
                    break;
                case QM_EDGE:
                    create_texture_wall(sprite, 7, 1 + h, victor);
                    break;
                case ZP_EDGE:
                    create_texture_wall(sprite, 8, 1 + h, victor);
                    break;
                case ZM_EDGE:
                    create_texture_wall(sprite, 6, 3 + h, victor);
                    break;
                case PM_EDGE:
                    create_texture_wall(sprite, 8, 2 + h, victor);
                    break;
                case QZP_EDGE:
                    create_texture_wall(sprite, 7, 3 + h, victor);
                    break;
                case QZM_EDGE:
                    create_texture_wall(sprite, 7, 4 + h, victor);
                    break;
                case ZPM_EDGE:
                    create_texture_wall(sprite, 8, 4 + h, victor);
                    break;
                case QPM_EDGE:
                    create_texture_wall(sprite, 8, 3 + h, victor);
                    break;
                case QZPM_EDGE:
                    create_texture_wall(sprite, 12, 2 + h, victor);
                    break;
                case MUSH_LCORNER:
                    create_texture_wall(sprite, 10, 2 + h, victor);
                    break;
                case MUSH_RCORNER:
                    create_texture_wall(sprite, 9, 2 + h, victor);
                    break;
                case AMOGUS:
                    create_texture_wall(sprite, 11, 1 + h, victor);
                    break;
                case AMOGUS2:
                    create_texture_wall(sprite, 10, 2 + h, victor);
                    break;
                case AMOGUS3:
                    create_texture_wall(sprite, 10, 4 + h, victor);
                    break;
                case AMOGUS4:
                    create_texture_wall(sprite, 10, 3 + h, victor);
                    break;

                case WALL:
                    create_texture_wall(sprite, 2, 2 + h, victor);
                    break;
            }
        }
    }
}


void map_draw_bridges(int matrix[64][64], Texture2D sprite, Texture2D sprite_b){
    Vector2 victor;
    for (int y = 0; y < 64; y++){
        for (int x = 0; x < 64; x++){
            victor = (Vector2){x * TILE,y * TILE};
            switch (matrix[y][x]) {
                case L_FBRIDGE_END:
                    create_texture_bridge(sprite_b, 11, 14, victor);
                    break;
                case H_FBRIDGE:
                    create_texture_bridge(sprite_b, 12, 14, victor);
                    break;
                case R_FBRIDGE_END:
                    create_texture_bridge(sprite_b, 10, 14, victor);
                    break;
                case U_FBRIDGE_END:
                    create_texture_bridge(sprite_b, 15, 18, victor);
                    break;
                case V_FBRIDGE:
                    create_texture_bridge(sprite_b, 15, 19, victor);
                    break;
                case D_FBRIDGE_END:
                    create_texture_bridge(sprite_b, 15, 20, victor);
                    break;
                case L_WBRIDGE_END:
                    create_texture_bridge(sprite_b, 11, 13, victor);
                    break;
                case H_WBRIDGE:
                    create_texture_bridge(sprite_b, 12, 13, victor);
                    break;
                case R_WBRIDGE_END:
                    create_texture_bridge(sprite_b, 10, 13, victor);
                    break;
                case L_WEND:
                    create_texture_bridge(sprite_b, 11, 14, victor);
                    create_texture_bridge(sprite_b, 11, 13, victor);
                    break;
                case H_DFLOOR:
                    create_texture_bridge(sprite_b, 12, 14, victor);
                    create_texture_bridge(sprite_b, 12, 13, victor);
                    break;
                case R_WEND:
                    create_texture_bridge(sprite_b, 10, 14, victor);
                    create_texture_bridge(sprite_b, 10, 13, victor);
                    break;

                case LU_WBRIDGE_END:
                    create_texture_bridge(sprite_b, 14, 18, victor);
                    break;
                case LV_WBRIDGE:
                    create_texture_bridge(sprite_b, 14, 19, victor);
                    break;
                case LD_WBRIDGE_END:
                    create_texture_bridge(sprite_b, 14, 20, victor);
                    break;
                case RU_WBRIDGE_END:
                    create_texture_bridge(sprite_b, 16, 18, victor);
                    break;
                case RV_WBRIDGE:
                    create_texture_bridge(sprite_b, 16, 19, victor);
                    break;
                case RD_WBRIDGE_END:
                    create_texture_bridge(sprite_b, 16, 20, victor);
                    break;

                case GRASS:
                    create_texture_decor(sprite, 2, 1, victor);
                    break;
                case PATH_1:
                    create_texture_decor(sprite, 4, 1, victor);
                    break;
                case PATH_2:
                    create_texture_decor(sprite, 5, 1, victor);
                    break;
                case PATH_3:
                    create_texture_decor(sprite, 4, 2, victor);
                    break;
                case PATH_4:
                    create_texture_decor(sprite, 5, 2, victor);
                    break;
                case BMUSH:
                    create_texture_decor(sprite, 6, 1, victor);
                    break;
                case RMUSH:
                    create_texture_decor(sprite, 8, 1, victor);
                    break;

                default:
                    break;
            }
        }
    }
}