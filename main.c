#include "raylib.h"
#define SCREEN_SIZE_WIDTH 700
#define SCREEN_SIZE_HEIGHT 400


int main(void){

    Texture2D sprite;
    Sound sound;
    Music music;

    InitWindow(SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, "The best Window");
    InitAudioDevice();

    sprite = LoadTexture("carita.png");
    sound = LoadSound("sound.mp3");
    music = LoadMusicStream("song.mp3");
    PlayMusicStream(music);

    SetTargetFPS(144);

    float posX = 0;
    float posY = 0;
    int rebotarX = 1;
    int rebotarY = 1;

    while(!WindowShouldClose()) {

        UpdateMusicStream(music);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(sprite, posX, posY, WHITE);

        EndDrawing();

        posX += GetFrameTime() * 100 * rebotarX;
        posY += GetFrameTime() * 100 * rebotarY;

        if (posX >= SCREEN_SIZE_WIDTH -16 || posX <= 0){
            rebotarX *= -1;
            PlaySound(sound);
        }

        if (posY >= SCREEN_SIZE_HEIGHT -16 || posY <= 0){
            rebotarY *= -1;
            PlaySound(sound);
        }

    }
    StopMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}