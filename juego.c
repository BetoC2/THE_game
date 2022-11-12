
#include "juego.h"
#include "global.h"

struct player{
    Rectangle hitbox;
    int vidas;
    int side[2];
    float speed;
    //sprite
    //Rectangle arma
};


Player* create_player(){
    Player* jugador = malloc(sizeof(Player));
    jugador->hitbox = create_hitbox(S_WIDHT/3.0,S_HEIGHT/2.0);
    jugador->vidas = 3;
    jugador->speed = 3.5;
    jugador->side[0] = 0;
    jugador->side[1] = 0;
    return jugador;
}

//Tanto esta función como la de abajo podrían combinarse, para dibujar bien el sprite
void draw_player(Player* a){
    DrawRectangleRec(a->hitbox,YELLOW);
}

void move_player(Player* a){
    if(IsKeyDown(KEY_W) && a->side[0] != 3 && a->side[1] != 3) a->hitbox.y -= a->speed;    //Arriba
    if(IsKeyDown(KEY_S) && a->side[0] != 1 && a->side[1] != 1) a->hitbox.y += a->speed;    //Abajo
    if(IsKeyDown(KEY_A) && a->side[0] != 2 && a->side[1] != 2) a->hitbox.x -= a->speed;    //Izquierda
    if(IsKeyDown(KEY_D) && a->side[0] != 4 && a->side[1] != 4) a->hitbox.x += a->speed;    //Derecha
}