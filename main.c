
#include "juego.h"
#include "global.h"

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

    InitWindow(S_WIDHT, S_HEIGHT, "vamos viendo gente");

    SetTargetFPS(60);           // Poner el juego a 60 frames
    Player* a = create_player();

    // EL JUEGO
    while (!WindowShouldClose())    //Ver si se presiona esc o cierran la ventana
    {
        // Update


        BeginDrawing(); //---------------------

        ClearBackground(RAYWHITE);

        fondo();
        move_player(a);

        draw_player(a);

        EndDrawing(); //-----------------------

    }

    CloseWindow();

    return 0;
}