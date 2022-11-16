
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
    InitWindow(S_WIDHT, S_HEIGHT, "Coconut doggy");

    SetTargetFPS(60);           // Poner el juego a 60 frames
    Player* jugador = create_player();
    List * paredes = (crate_walls());

    int xd = 0;     //XD, luego se quita


    // YO SOY EL JUEGO :O
    while (!WindowShouldClose())    //Ver si se presiona esc o cierran la ventana
    {
        // Cambios
        xd ++;          //Probando cosas que ocupan tiempo y delete
        if(xd == 300)
            list_delete(paredes, 5);


        chocar_paredes( jugador, paredes);
        move_player(jugador);




        BeginDrawing(); //---------------------


        ClearBackground(RAYWHITE);

        fondo();
        draw_walls(paredes);
        draw_player(jugador);


        EndDrawing(); //-----------------------

    }

    CloseWindow();

    return 0;
}