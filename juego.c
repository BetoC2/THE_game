
#include "juego.h"


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
    DrawRectangleRec(a->hitbox,LIGHTGRAY);
    a->side[0] = 0;
    a->side[1] = 0;
}

void move_player(Player* a){
    if(IsKeyDown(KEY_W) && a->side[0] != 3 && a->side[1] != 3) a->hitbox.y -= a->speed;    //Arriba
    if(IsKeyDown(KEY_S) && a->side[0] != 1 && a->side[1] != 1) a->hitbox.y += a->speed;    //Abajo
    if(IsKeyDown(KEY_A) && a->side[0] != 2 && a->side[1] != 2) a->hitbox.x -= a->speed;    //Izquierda
    if(IsKeyDown(KEY_D) && a->side[0] != 4 && a->side[1] != 4) a->hitbox.x += a->speed;    //Derecha
}

void chocar_paredes(Player* p, Walls* w){
    float dif_x;
    float dif_y;
    int side;

    for(int i = 0; i < w->size; i++){

        if(CheckCollisionRecs(p->hitbox,w->array[i])) {
            DrawRectangle(50, 30, 250, 250, ORANGE);

            dif_x = p->hitbox.x - w->array[i].x;
            dif_x = dif_x < 0? dif_x * -1: dif_x;
            dif_y= p->hitbox.y - w->array[i].y;
            dif_y = dif_y < 0? dif_y * -1: dif_y;

            if (dif_x < SIZE && dif_x <= dif_y)
                side = (p->hitbox.y - w->array[i].y) < 0? 1: 3;
            else if (dif_y < SIZE && dif_x >= dif_y)
                side = (p->hitbox.x - w->array[i].x) < 0? 4: 2;

        }
        else
            continue;

        if(p->side[0] == 0)
            p->side[0] = side;
        else
            p->side[1] = side;
    }
}