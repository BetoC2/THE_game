
#include "juego.h"
#include "global.h"
#include "map.h"

//Esto solo está de mientras, luego lo quitamos
void fondo() {
    int color = 0;

    for(int x = 0; x < 16; x++) {
        for(int y = 0; y < 10; y++){
            if (color) {
                DrawRectangle(64 * x, 64 * y, 64, 64, VIOLET);
            }
            else {
                DrawRectangle(64 * x, 64 * y, 64, 64, BLACK);
            }
            color = color? 0: 1;
        }
        color = color? 0: 1;
    }
}

int main(void)
{
    InitWindow(S_WIDHT, S_HEIGHT, "Coconut doggy");

    srand(time(NULL));
    SetTargetFPS(FPS);           // Poner el juego a 60 frames

    int map[64][64];
    int bridges[64][64];
    Vector2 initial_position;
    map_generate(map, bridges, &initial_position);

    Player* jugador = create_player();
    List* paredes = crate_walls();
    List* enemigos = summon_enemies();
    List* awas_tiradas = spawn_awas();

    int se_perdio;


    // YO SOY EL JUEGO :O
    while (!WindowShouldClose())    //Ver si se presiona esc o cierran la ventana
    {

        // Cambios
        chocar_paredes( jugador, paredes);
        manage_awa(awas_tiradas, jugador);
        se_perdio = manage_player(jugador);
        if(se_perdio)
            break;
        manage_enemies(jugador, enemigos, awas_tiradas);




        BeginDrawing(); //---------------------


        ClearBackground(RAYWHITE);

        fondo();
        draw_walls(paredes);
        draw_enemies(enemigos);
        draw_player(jugador);
        draw_awa(awas_tiradas);



        EndDrawing(); //-----------------------

    }

    CloseWindow();
    if(rand()%2 && se_perdio)
        OpenURL("https://www.youtube.com/watch?v=RmUWWVZw28E");
    else if(se_perdio)
        OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");

    return 0;
}
