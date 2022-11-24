#include "map.h"

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
    rooms_fill(rooms, x, y, 6+rep);
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

void rooms_replace(int matrix[64][64], int x, int y, char *name){
    int map[16][16];
    rooms_load(map, name);
    rooms_get_spawn(map);

    for (int i = y, b = 0; (i < y + TILE) && b < 16; i++,b++){
        for(int j = x, a = 0; (j < x + TILE) && a < 16; j++, a++){
            matrix[i][j] = map[b][a];
        }
    }
}

void rooms_insert(int matrix[64][64], int rooms[4][4]){
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

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (rooms[j][i] == 1){
                int random = rand() % 7;
                int x = i * TILE;
                int y = j * TILE;
                rooms_replace(matrix, x, y, files[random]);
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
    matrix[y_index+2][x_start] =  L_WBRIDGE_END;
    x_start++;

    while (x_start < x_final){
        matrix[y_index-1][x_start] = H_WBRIDGE;
        matrix[y_index][x_start] = H_FBRIDGE;
        matrix[y_index+1][x_start] = H_FBRIDGE;
        matrix[y_index+2][x_start] =  H_WBRIDGE;
        x_start++;
    }

    matrix[y_index-1][x_start] = R_WBRIDGE_END;
    matrix[y_index][x_start] = R_FBRIDGE_END;
    matrix[y_index+1][x_start] = R_FBRIDGE_END;
    matrix[y_index+2][x_start] =  R_WBRIDGE_END;
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
    matrix[y_start][x_index] = D_FBRIDGE_END;
    matrix[y_start][x_index+1] = D_FBRIDGE_END;
    matrix[y_start][x_index+2] = RD_WBRIDGE_END;
}

void map_generate(int matrix[64][64], int bridges[64][64]){
    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++){
            matrix[i][j] = 0;
        }
    }

    int rooms[4][4];
    rooms_generate(rooms);
    rooms_insert(matrix, rooms);
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
}

void map_draw(int matrix[64][64]){
    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++){
            switch (matrix[i][j]) {
                case FLOOR:
                    DrawRectangle(j * TILE, i * TILE, TILE, TILE, DARKGREEN);
                    break;

                case FLOOR_SPAWN:
                    DrawRectangle(j * TILE, i * TILE, TILE, TILE, ORANGE);
                    break;

                case L_FBRIDGE_END:
                case H_FBRIDGE:
                case R_FBRIDGE_END:
                case U_FBRIDGE_END:
                case V_FBRIDGE:
                case D_FBRIDGE_END:
                    DrawRectangle(j * TILE, i * TILE, TILE, TILE, GRAY);
                    break;

                case L_WBRIDGE_END:
                case H_WBRIDGE:
                case R_WBRIDGE_END:
                case LU_WBRIDGE_END:
                case LV_WBRIDGE:
                case LD_WBRIDGE_END:
                case RU_WBRIDGE_END:
                case RV_WBRIDGE:
                case RD_WBRIDGE_END:
                    DrawRectangle(j * TILE, i * TILE, TILE, TILE, DARKGRAY);
                    break;

                case L_WALL:
                case LR_WALL:
                case LU_WALL:
                case LD_WALL:
                case LRU_WALL:
                case LRD_WALL:
                case LRUD_WALL:
                case R_WALL:
                case RU_WALL:
                case RD_WALL:
                case RUD_WALL:
                case U_WALL:
                case UD_WALL:
                case D_WALL:
                case LUD_WALL:
                    DrawRectangle(j * TILE, i * TILE, TILE, TILE, DARKBLUE);
                    break;

                case Q_EDGE:
                case Z_EDGE:
                case P_EDGE:
                case M_EDGE:
                case QZ_EDGE:
                case QP_EDGE:
                case QM_EDGE:
                case ZP_EDGE:
                case ZM_EDGE:
                case PM_EDGE:
                case QZP_EDGE:
                case QZM_EDGE:
                case ZPM_EDGE:
                case QPM_EDGE:
                case QZPM_EDGE:
                    DrawRectangle(j * TILE, i * TILE, TILE, TILE, BLUE);
                    break;

                case WALL:
                    DrawRectangle(j * TILE, i * TILE, TILE, TILE, SKYBLUE);
                    break;

                default:
                    DrawRectangle(j * TILE, i * TILE, TILE, TILE, BLACK);
                    break;
            }
        }
    }
}
