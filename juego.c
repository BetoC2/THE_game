
#include "juego.h"
#include "librarby.h"
#include "map.h"

//Estructuras

struct player{
    Rectangle hitbox;   // Ubicación y colisión
    Rectangle arma;     // hitbox del ataque
    int vida;           // Vida en medios corazones
    int side[2];        // Posiciones a donde no avanzar (para paredes)
    float speed;        // Velocidad (pixeles x frames)
    int damage;
    int facing;         // 1 arriba, 2 derecha, 3 abajo, 4 izquierda
    int state;          // Atacando o no, 0 y 1
    List* awas;         // Pociones a la mano
    int timer_damage;
    int timer_atack;
    int timer_awas;
    Camera2D camara;
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
    int damage;
    float vision;       // Distancia (en tiles) de seguimiento
    int timer;          //Evita recibir mucho daño
    //sprite            // Futuro sprite
};

struct awas{
    int sabor;
    Rectangle ubicacion;
    // Sprite
};

struct floor{
    Rectangle place;
    int tipo;           //De mientras, se borra después
    //Vector?
    //2D coso
};


//AWAS

List* spawn_awas(Vector2* v){
    List* l = new_list();
    AwasdeSabor* a = malloc(sizeof(AwasdeSabor));

    a->sabor = rand()%3 + 1;
    a->ubicacion = create_hitbox((v->x + 7) * SIZE, v->y * SIZE);
    list_add(l,a);

    return l;

};

void draw_awa(List* l){

    for(int i = 0; i < list_size(l); i++){
        AwasdeSabor* a = list_get(l,i);
        DrawRectangleRec(a->ubicacion, GREEN);
    }
}

void manage_awa(List* l, Player* p){

    for(int i = 0; i < list_size(l); i++){
        AwasdeSabor* a = list_get(l, i);

        if(CheckCollisionRecs(p->hitbox, a->ubicacion)){
            list_delete(l, i);
            list_add(p->awas, a);
        }

    }
}

void drop_awa(List* l, Rectangle r){
    AwasdeSabor* a = malloc(sizeof(AwasdeSabor));
    a->sabor = rand()%3 + 1;
    a->ubicacion = r;

    list_add(l, a);
}


// JUGADOR
Player* create_player(Vector2* v){
    Player* jugador = malloc(sizeof(Player));
    jugador->hitbox = create_hitbox(v->x * SIZE,v->y * SIZE);

    jugador->vida = 5;
    jugador->speed = velocidad(3.5f);
    jugador->damage = 1;
    jugador->side[0] = 0;
    jugador->side[1] = 0;
    jugador->state = 0;
    jugador->timer_atack = 0;
    jugador->timer_damage = 0;
    jugador->timer_awas = 0;
    jugador->facing = 3;
    jugador->arma = hitbox_arma(jugador->facing, jugador->hitbox.x, jugador->hitbox.y);
    jugador->awas = new_list();

    return jugador;
}

void draw_player(Player* p){
    if(p->timer_atack > FPS)
        DrawRectangleRec(p->arma, ORANGE);

    if(p->timer_damage % 16 > 8 || p->timer_damage < 16)
        DrawRectangleRec(p->hitbox,LIGHTGRAY);

    if(list_size(p->awas)) {

        AwasdeSabor *a = list_peek(p->awas);
        Color awa = !a->sabor ? WHITE : a->sabor == 1 ? RED : a->sabor == 2 ? GREEN : BLUE;

        DrawCircle(p->hitbox.x + 160, p->hitbox.y - 96, SIZE/2.0, awa);
    }

    for(int i = 0; i < p->vida; i++)
        DrawCircle(p->hitbox.x + SIZE * (i * 1.1)  - 160, p->hitbox.y - 96, SIZE/2.0, RED);

}   //ESTO SE VA A CAMBIAR
    //cosas de manage
void move_player(Player* p){
    if(IsKeyDown(KEY_W) && p->side[0] != 3 && p->side[1] != 3) p->hitbox.y -= p->speed;    //Arriba
    if(IsKeyDown(KEY_S) && p->side[0] != 1 && p->side[1] != 1) p->hitbox.y += p->speed;    //Abajo
    if(IsKeyDown(KEY_A) && p->side[0] != 2 && p->side[1] != 2) p->hitbox.x -= p->speed;    //Izquierda
    if(IsKeyDown(KEY_D) && p->side[0] != 4 && p->side[1] != 4) p->hitbox.x += p->speed;    //Derecha

    if(IsKeyDown(KEY_W)) p->facing = 1;
    if(IsKeyDown(KEY_S)) p->facing = 3;
    if(IsKeyDown(KEY_D)) p->facing = 2;
    if(IsKeyDown(KEY_A)) p->facing = 4;
}

void ataque_player(Player* p){
    if(IsKeyPressed(KEY_SPACE) && !p->timer_atack){
        p->timer_atack = FPS * 1.5;
    }
    if(p->timer_atack)
        p->timer_atack--;
}

void use_awas(Player* p){
    if(IsKeyDown(KEY_LEFT_SHIFT) && !p->timer_awas && list_size(p->awas)){
        AwasdeSabor* a = list_pop(p->awas);
        p->timer_damage += FPS / 2;
        p->timer_atack += FPS / 2;

        if(a->sabor == 1)
            p->vida += 3;

        if(a->sabor == 2){
            p->speed += velocidad(2.5f);
            p->timer_awas += FPS * 6;
        }
        if(a->sabor == 3){
            p->damage += 2;
            p->timer_awas += FPS * 5;
        }
    }

    if(p->timer_awas){
        p->timer_awas--;
        if(!p->timer_awas){
            p->damage = 1;
            p->speed = velocidad(3.5f);
        }
    }
}

int manage_player(Player* p){

    move_player(p);

    p->arma = hitbox_arma(p->facing, p->hitbox.x, p->hitbox.y);
    ataque_player(p);
    use_awas(p);

    p->side[0] = 0;
    p->side[1] = 0;

    if(p->vida<=0)
        return 1;
    else
        return 0;
}


//PAREDES
List* crate_walls(int map[64][64]){
    List* l  = new_list();

    for (int i = 0; i < 64; ++i) {      // i = y
        for (int j = 0; j < 64; ++j) {      //j = x
            if(map[i][j] < WALL && map[i][j] >= RV_WBRIDGE){
                Wall* w = malloc(sizeof(Wall));
                w->hitbox = create_hitbox((float)j * SIZE, (float)i * SIZE);
                list_add(l, w);
            }
        }
    }

    return l;
}   //ESTO USA LA MATRIZ POR GENERACIÓN DE BETO

void draw_walls(List* l){
    for(int i = 0; i < list_size(l); i++){
        Wall* w = list_get(l, i);
        DrawRectangleRec(w->hitbox,YELLOW);
    }

}
    //cosas de manage
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
        case 1: //Pequeño y rápido
            e->vida = 4;
            e->speed = velocidad(2.75f);
            e->damage = 1;
            e->vision = 3.5f;
            break;
        case 2: //Tanque
            e->vida = 10;
            e->speed = velocidad(1);
            e->damage = 2;
            e->vision = 6;
            break;
        default:    //Por defecto e inutil XD
            e->vida = 1;
            e->speed = velocidad(0.5f);
            e->damage = 0;
            e->vision = 0.5f;
    }
}

List* summon_enemies(int map[64][64]){
    List* l = new_list();

    for (int i = 0; i < 64; ++i) {      // i = y
        for (int j = 0; j < 64; ++j) {      //j = x
            if(map[i][j] == FLOOR_SPAWN){
                Enemy* e = malloc(sizeof(Enemy));
                e->type = rand()%2 + 1;
                e->hitbox = create_hitbox((float)j * SIZE, (float)i * SIZE);
                e->timer = 0;
                asign_stats(e);
                list_add(l,e);

            }
        }
    }

    return l;
}

void draw_enemies(List* l){
    for (int i = 0; i < list_size(l); ++i) {
        Enemy* e = list_get(l, i);
        Color c = e->type == 1? BLUE: RED;

        if(e->timer % 16 > 8 || e->timer < 16)
            DrawRectangleRec(e->hitbox, c);
    }
}      //ESTO SE VA A CAMBIAR
    //cosas de manage
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

void lastimar_atacar(Player* p, Enemy* e){

    // Daño a enemigo
    if(CheckCollisionRecs(p->arma, e->hitbox) && !e->timer && p->timer_atack > FPS) {
        e->timer = FPS * 1.5;
        e->vida -= p->damage;
    }
    if(e->timer)
        e->timer--;


    // Daño a jugador
    if(CheckCollisionRecs(p->hitbox, e->hitbox) && !p->timer_damage){
        p->timer_damage += FPS * 1.5;
        p->vida -= e->damage;
    }
    if(p->timer_damage)
        p->timer_damage--;




}

void manage_enemies(Player* p, List* l, List* a){

    for(int i = 0; i < list_size(l); i++){
        Enemy* e = list_get(l,i);

        move_enemies(p, e);
        lastimar_atacar(p, e);

        if(e->vida<=0) {
            if(rand()% 5 < 1)         //QUE SEA UN 20%
                drop_awa(a, e->hitbox);

            list_delete(l, i);
        }
    }
}


List* crear_suelo(){
    List* l = new_list();

    return l;
};



//CAMARA
Camera2D crear_camara(Player* p){
    Camera2D camara;
    camara.zoom = 48.0f / SIZE;    // El primer número es el tamaño mostrado en pixeles
    camara. rotation = 0;
    camara.offset = (Vector2){S_WIDHT/2.0 , S_HEIGHT/2.0};
    update_camara(p, &camara);

    return  camara;
}

void update_camara(Player* p, Camera2D* c){
    c->target = (Vector2){p->hitbox.x,p->hitbox.y};
}


