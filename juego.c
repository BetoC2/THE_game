
#include "juego.h"
#include "global.h"

struct player{
    Rectangle hitbox;
    int vidas;
    int side[2];
    //sprite
    //Rectangle
};

Player* create_player(){
    Player* jugador = malloc(sizeof(Player));
    jugador->hitbox = create_hitbox(S_WIDHT/3.0,S_HEIGHT/2.0);
    jugador->vidas = 3;
    return jugador;
}

void draw_player(Player* a){
    DrawRectangleRec(a->hitbox,YELLOW);
}

void move_player(Player* a){
    if(IsKeyDown(KEY_W) && *(a->side) != 3 && a->side[1] != 3) a->hitbox.y -= 4;    //Arriba
    if(IsKeyDown(KEY_S) && *(a->side) != 1 && a->side[1] != 1) a->hitbox.y += 4;    //Abajo
    if(IsKeyDown(KEY_A) && *(a->side) != 2 && a->side[1] != 2) a->hitbox.x -= 4;    //Izquierda
    if(IsKeyDown(KEY_D) && *(a->side) != 4 && a->side[1] != 4) a->hitbox.x += 4;    //Derecha
}