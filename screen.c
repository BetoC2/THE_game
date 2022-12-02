#include "screen.h"
#include <stdio.h>

int screen_title(int map[64][64], int bridges[64][64], int *water_temp, Camera2D camara,
                 Font fuente, Texture2D sprite_w, Texture2D sprite_d, Texture2D sprite_decor){

    float start_x = camara.target.x - (10*TILE);
    float start_y = camara.target.y - (5.5*TILE);
    float start_width = (6 * TILE) + 7;

    float quit_x = start_x;
    float quit_y = camara.target.y - (4*TILE);
    float quit_width = (6 * TILE) + 7;

    Vector2 vec_start = {camara.target.x - (10*TILE) +2,camara.target.y - (5.5 * TILE) +2};
    Vector2 vec_quit = {camara.target.x - (10*TILE) +2, camara.target.y - (4*TILE) +2};

    Rectangle position_start =  {start_x, start_y, start_width ,TILE};
    Rectangle position_quit = {quit_x,quit_y, quit_width,TILE};


    while(!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camara);

            if (mouse.x >= start_x && mouse.x <= start_x + start_width){
                if(mouse.y >= start_y && mouse.y <= start_y + TILE)
                    return 1;
            }

            if (mouse.x >= quit_x && mouse.x <= quit_x + quit_width){
                if(mouse.y >= quit_y && mouse.y <= quit_y + TILE)
                    return 0;
            }
        }

        BeginDrawing(); //---------------------
        BeginMode2D(camara);

        ClearBackground(WATER);

        map_draw(map, sprite_w, water_temp);
        map_draw_bridges(bridges, sprite_decor, sprite_d);

        DrawRectangleRec(position_start, LIGHTGRAY);
        DrawRectangleRec(position_quit, LIGHTGRAY);

        DrawTextEx(fuente, "Iniciar partida", vec_start, 10, .05, BLACK);
        DrawTextEx(fuente, "Salir del juego", vec_quit, 10, .05, BLACK);

        EndMode2D();
        EndDrawing(); //-----------------------

    }
    return 0;
}

int screen_pause(int map[64][64], int bridges[64][64], int *water_temp, Camera2D camara,
                 Font fuente, Texture2D sprite_w, Texture2D sprite_d, Texture2D sprite_decor){

    float start_x = camara.target.x - (10 * TILE);
    float start_y = camara.target.y - (5.5 * TILE);
    float start_width = (6 * TILE) + 7;

    float quit_x = start_x;
    float quit_y = camara.target.y - (4 * TILE);
    float quit_width = (6 * TILE) + 7;

    Vector2 vec_start = {camara.target.x - (10 * TILE) + 2, camara.target.y - (5.5 * TILE) + 2};
    Vector2 vec_quit = {camara.target.x - (10 * TILE) + 2, camara.target.y - (4 * TILE) + 2};

    Rectangle position_start = {start_x, start_y, start_width, TILE};
    Rectangle position_quit = {quit_x, quit_y, quit_width, TILE};


    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camara);

            if (mouse.x >= start_x && mouse.x <= start_x + start_width) {
                if (mouse.y >= start_y && mouse.y <= start_y + TILE)
                    return 1;
            }

            if (mouse.x >= quit_x && mouse.x <= quit_x + quit_width) {
                if (mouse.y >= quit_y && mouse.y <= quit_y + TILE)
                    return 0;
            }
        }

        BeginDrawing(); //---------------------
        BeginMode2D(camara);

        ClearBackground(WATER);

        map_draw(map, sprite_w, water_temp);
        map_draw_bridges(bridges, sprite_decor, sprite_d);

        DrawRectangleRec(position_start, LIGHTGRAY);
        DrawRectangleRec(position_quit, LIGHTGRAY);

        DrawTextEx(fuente, "Continuar juego", vec_start, 10, .05, BLACK);
        DrawTextEx(fuente, "Salir del juego", vec_quit, 10, .05, BLACK);

        EndMode2D();
        EndDrawing(); //-----------------------
    }
    return 0;
}

int screen_update(int map[64][64], int bridges[64][64], int *water_temp, Camera2D camara,
                   Font fuente, Texture2D sprite_w, Texture2D sprite_d, Texture2D sprite_decor){

    if (IsKeyDown(KEY_P)) {
        if (!screen_pause(map, bridges, water_temp, camara, fuente, sprite_w, sprite_d, sprite_decor))
            return 0;
    }
    return 1;
}