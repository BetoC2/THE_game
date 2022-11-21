
#include "juego.h"
#include "librarby.h"

//Estructuras
struct player{
    Rectangle hitbox;   // Ubicación y colisión
    Rectangle arma;     // hitbox del ataque
    int vida;           // Vida en medios corazones
    int side[2];        // Posiciones a donde no avanzar (para paredes)
    float speed;        // Velocidad (pixeles x frames)
    int facing;         // 1 arriba, 2 derecha, 3 abajo, 4 izquierda
    int state;          // Atacando o no, 0 y 1
    int timer_damage;
    int timer_atack;
    //sprite
};

struct wall{
    Rectangle hitbox;   // Posición y zona de colisión
    //Sprite ??         // Futuro sprite
};

struct enemy{
    Rectangle hitbox;   // Posición y zona de choque
    int type;           // Tipo de enemigo
    int vida;           // Cantidad de vida
    float speed;        // Velocidad (Pixeles x frame)
    float vision;       // Distancia (en tiles) de seguimiento
    //sprite            // Futuro sprite
};

// JUGADOR
Player* create_player(){
    Player* jugador = malloc(sizeof(Player));
    jugador->hitbox = create_hitbox(S_WIDHT/3.0,S_HEIGHT/2.0);
    jugador->vida = 3;
    jugador->speed = 4;
    jugador->side[0] = 0;
    jugador->side[1] = 0;
    jugador->timer_atack = 0;
    jugador->timer_damage = 0;
    jugador->facing = 3;
    jugador->arma = hitbox_arma(jugador->facing, jugador->hitbox.x, jugador->hitbox.y);
    return jugador;
}

void draw_player(Player* p){
    DrawRectangleRec(p->arma, ORANGE);
    DrawRectangleRec(p->hitbox,LIGHTGRAY);
    Color c;
}

    //cosas de manage
void move_player(Player* p){
    if(IsKeyDown(KEY_W) && p->side[0] != 3 && p->side[1] != 3) p->hitbox.y -= p->speed;    //Arriba
    if(IsKeyDown(KEY_S) && p->side[0] != 1 && p->side[1] != 1) p->hitbox.y += p->speed;    //Abajo
    if(IsKeyDown(KEY_A) && p->side[0] != 2 && p->side[1] != 2) p->hitbox.x -= p->speed;    //Izquierda
    if(IsKeyDown(KEY_D) && p->side[0] != 4 && p->side[1] != 4) p->hitbox.x += p->speed;    //Derecha
}

void lado_player(Player* p){    //Necesita afinación, pero funciona
    if(IsKeyDown(KEY_W)) p->facing = 1;
    if(IsKeyDown(KEY_S)) p->facing = 3;
    if(IsKeyDown(KEY_D)) p->facing = 2;
    if(IsKeyDown(KEY_A)) p->facing = 4;


}

void manage_player(Player* p){

    lado_player(p);
    move_player(p);
    p->arma = hitbox_arma(p->facing, p->hitbox.x, p->hitbox.y);


    p->side[0] = 0;
    p->side[1] = 0;

}


//PAREDES
List* crate_walls(){
    List* l  = new_list();

    float mien_x[11] = {2,2,2,3,8,9,10,10,8,10,12};
    float mien_y[11] = {6,7,8,2,1,1,2,3,5,7,7};

    for(int i = 0; i < 11; i++){
        Wall* w = malloc(sizeof(Wall));
        w->hitbox = create_hitbox(mien_x[i]*SIZE, mien_y[i]*SIZE);
        list_add(l, w);
    }
    return l;
}   //ESTO USA LA MATRIZ POR GENERACIÓN DE BETO

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


//ENEMIGOS
void asign_stats(Enemy* e){
    switch (e->type) {
        case 1:
            e->vida = 4;
            e->speed = 2.75f;
            e->vision = 3;
            break;
        case 2:
            e->vida = 10;
            e->speed = 1;
            e->vision = 4;
            break;
        default:
            e->vida = 1;
            e->speed = 0.5f;
            e->vision = 0.5f;
    }
}

List* summon_enemies(){
    List* l = new_list();

    float mien_x[2] = {14, 0};
    float mien_y[2] = {1, 9};

    for(int i = 0; i < 2; i++){
        Enemy* e = malloc(sizeof(Enemy));
        e->type = rand()%2 + 1;
        e->hitbox = create_hitbox(mien_x[i] * SIZE, mien_y[i] * SIZE);
        asign_stats(e);
        list_add(l,e);
    }
    return l;
}

void draw_enemies(List* l){
    for (int i = 0; i < list_size(l); ++i) {
        Enemy* e = list_get(l, i);
        Color c = e->type == 1? BLUE: RED;
        DrawRectangleRec(e->hitbox, c);

    }
}

void move_enemies(Player* p, Enemy* e){

    // Podemos usar un estado (tranquilo/ agresivo) o un radio mayor en un futuro
    if(distance(p->hitbox, e->hitbox) > (e->vision + 1) * SIZE) {
        return;   //Movimiento natural
    }

    // Movimiento atacando estandar
    float movement_x = p->hitbox.x - e->hitbox.x;
    float movement_y = p->hitbox.y - e->hitbox.y;
    int dir_x = movement_x > 0? 1: -1;
    int dir_y = movement_y > 0? 1: -1;

    float total = (movement_x * dir_x) + (movement_y * dir_y);

    movement_x = movement_x / total * e->speed;
    movement_y = movement_y / total * e->speed;

    e->hitbox.x += movement_x;
    e->hitbox.y += movement_y;

}

void manage_enemies(Player* p, List* l){

    for(int i = 0; i < list_size(l); i++){
        Enemy* e = list_get(l,i);

        //Funciones a usar
        move_enemies(p, e);
    }
}