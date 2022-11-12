
#include "juego.h"
#include "global.h"

int main(void)
{

    InitWindow(S_WIDHT, S_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        BeginDrawing(); //---------------------

        ClearBackground(RAYWHITE);

        DrawText("Estamos empezando joven", S_WIDHT/2, S_HEIGHT/2, 20, LIGHTGRAY);

        EndDrawing(); //-----------------------

    }

    CloseWindow();

    return 0;
}