
#include "juego.h"

//Estructuras
struct player{
    Rectangle hitbox;
    int vidas;
    int side[2];
    float speed;
    //sprite
    //Rectangle arma
};

struct wall{
    Rectangle hitbox;
    //Sprite ??
};

// JUGADOR
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


//PAREDES
List* crate_walls(){
    List* l  = new_list();

    float mien_x[11] = {2,2,2,3,8,9,10,10,8,10,12};
    float mien_y[11] = {6,7,8,2,1,1,2,3,5,7,7};

    for(int i = 0; i < 11; i++){
        Wall* a = malloc(sizeof(Wall));
        a->hitbox = create_hitbox(mien_x[i]*SIZE, mien_y[i]*SIZE);
        list_add(l, a);
    }
    return l;
}

void draw_walls(List* l){
    for(int i = 0; i < list_size(l); i++){
        Wall* w = list_get(l, i);
        DrawRectangleRec(w->hitbox,YELLOW);
    }

}

void chocar_paredes(Player* p, List* w) {

    int side;

    for (int i = 0; i < list_size(w); i++) {

        Wall *curr = list_get(w, i);
        if (!CheckCollisionRecs(p->hitbox, curr->hitbox))
            continue;


        float dif_x = diferencia(p->hitbox.x, curr->hitbox.x);
        float dif_y = diferencia(p->hitbox.y, curr->hitbox.y);


        if (dif_x < SIZE && dif_x <= dif_y)
            side = (p->hitbox.y - curr->hitbox.y) < 0 ? 1 : 3;
        else if (dif_y < SIZE && dif_x >= dif_y)
            side = (p->hitbox.x - curr->hitbox.x) < 0 ? 4 : 2;

        if (p->side[0] == 0)
            p->side[0] = side;
        else
            p->side[1] = side;
    }
}
