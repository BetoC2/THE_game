
#include "juego.h"
#include "librarby.h"
#include "map.h"

//Estructuras
struct player{
    Rectangle hitbox;   // Ubicación y colisión
    Rectangle arma;     // hitbox del ataque
    int vida;           // Vida en medios corazones
    int max_vida;
    int side[2];        // Posiciones a donde no avanzar (para paredes)
    float speed;        // Velocidad (pixeles x frames)
    int damage;
    int facing;         // 1 arriba, 2 derecha, 3 abajo, 4 izquierda
    int state;          // Atacando o no, 0 y 1
    List* awas;         // Pociones a la mano
    int timer_damage;
    int timer_atack;
    int timer_awas;
};

struct enemy{
    Rectangle hitbox;   // Posición y zona de choque
    int type;           // Tipo de enemigo
    int vida;           // Cantidad de vida
    float speed;        // Velocidad (Pixeles x frame)
    int damage;
    float vision;       // Distancia (en tiles) de seguimiento
    int timer;          //Evita recibir mucho daño
    int facing;
    int timer_extra;
};

struct awas{
    int sabor;
    Rectangle ubicacion;
    Rectangle sprite;
};

struct wall{
    Rectangle hitbox;   // Posición y zona de colisión
};


//STATS Y EXTRAS
void draw_stats(Player* p, Texture2D spr, Camera2D c){

    Vector2 v;
    int potis;
    int size = list_size(p->awas);
    float esquina_x = p->hitbox.x + ((float)S_WIDHT/SIZE /2 - 2)/c.zoom * SIZE;
    float esquina_y =  p->hitbox.y - ((float)S_HEIGHT/SIZE /2 - 2)/c.zoom * SIZE;

    if(size) {
        potis = size > 3 ? 3: size;
        for (int i = 0, max = size - 1; i < potis; i++, max--) {
            AwasdeSabor *a = list_get(p->awas, max);
            v = (Vector2) {esquina_x - (i * SIZE), esquina_y};
            DrawTextureRec(spr, a->sprite, v, WHITE);
        }
    }

    for(int i = 0; i < p->vida; i++) {
        int cora = i < p->max_vida? 4: 5;
        Rectangle r = create_hitbox(0, (float)cora * 16);
        esquina_x =  p->hitbox.x - ((float)S_WIDHT/SIZE /2 - 2 - (float)i* c.zoom)/c.zoom * SIZE;
        v = (Vector2){esquina_x, esquina_y};
        DrawTextureRec(spr, r, v, WHITE);
    }


}

void matar_todo(Player* p, List* l_2, List* l_3, List* l_4){
    list_kill(p->awas);
    list_kill(l_2);
    list_kill(l_3);
    list_kill(l_4);
    free(p);

}


//AWAS
List* spawn_awas(Vector2* v){
    List* l = new_list();
    AwasdeSabor* a = malloc(sizeof(AwasdeSabor));

    a->sabor = rand()%4 + 1;
    a->ubicacion = create_hitbox((v->x + 7) * SIZE, v->y * SIZE);
    a->sprite = create_hitbox(0, (float)(a->sabor - 1) * 16);
    list_add(l,a);

    return l;
}

void draw_awa(List* l, Texture2D spr){
    for(int i = 0; i < list_size(l); i++){
        AwasdeSabor* a = list_get(l,i);
        Vector2 v = {a->ubicacion.x, a->ubicacion.y};
        DrawTextureRec(spr, a->sprite, v, WHITE);
    }
}

void manage_awa(List* l, Player* p){

    for(int i = 0; i < list_size(l); i++){
        AwasdeSabor* a = list_get(l, i);

        if(CheckCollisionRecs(p->hitbox, a->ubicacion)){
            list_delete(l, i);
            list_add(p->awas, a);
            break;
        }


    }
}

void drop_awa(List* l, Rectangle r){
    AwasdeSabor* a = malloc(sizeof(AwasdeSabor));
    a->sabor = (rand()%4) + 1;
    a->ubicacion = r;
    a->sprite = create_hitbox(0, (float)(a->sabor - 1) * 16);

    list_add(l, a);
}


// JUGADOR
Player* create_player(Vector2* v){
    Player* jugador = malloc(sizeof(Player));

    jugador->hitbox = (Rectangle){v->x * SIZE, v->y * SIZE, SIZE - 2, SIZE - 2};

    jugador->vida = 5;
    jugador->max_vida = 5;
    jugador->speed = velocidad(3.5f);
    jugador->damage = 1;

    jugador->side[0] = 0;
    jugador->side[1] = 0;
    jugador->state = 0;
    jugador->facing = 3;

    jugador->timer_atack = 0;
    jugador->timer_damage = 0;
    jugador->timer_awas = 0;

    jugador->arma = hitbox_arma(jugador->facing, jugador->hitbox.x, jugador->hitbox.y);
    jugador->awas = new_list();

    return jugador;
}

void draw_player(Player* p, Texture2D sprite, Texture2D hit, Texture2D sprite_r){
    Rectangle r = {0,(float)(p->facing - 1) * SIZE * 2,SIZE * 2,SIZE * 2};
    Vector2 v = {p->arma.x, p->arma.y};

    if(p->timer_atack > FPS)
        DrawTextureRec(hit, r, v, WHITE);
    
    if(p->timer_damage % 16 > 8 || p->timer_damage < 16){
        if(p->facing == 1){ //Arriba
            Rectangle recto = {0 * TILE, 0 * TILE, (float)sprite.width / 6, (float)sprite.height / 5};
            Vector2 victor = {p->hitbox.x -17, p->hitbox.y -27};
            DrawTextureRec(sprite, recto, victor, WHITE);
        }
        else if(p->facing == 3){ //Abajo
            Rectangle recto = {2 * TILE, 0 * TILE, (float)sprite_r.width / 6, (float)sprite_r.height / 5};
            Vector2 victor = {p->hitbox.x -33, p->hitbox.y -27};
            DrawTextureRec(sprite_r, recto, victor, WHITE);
        }
        else if(p->facing == 2){ //Derecha
            Rectangle recto = {5 * TILE, 0 * TILE, (float)sprite.width / 6, (float)sprite.height / 5};
            Vector2 victor = {p->hitbox.x-33, p->hitbox.y-27};
            DrawTextureRec(sprite, recto, victor, WHITE);
        }
        else if(p->facing == 4){ //Izquierda
            Rectangle recto = {0 * TILE, 0 * TILE, (float)sprite_r.width / 6, (float)sprite_r.height / 5};
            Vector2 victor = {p->hitbox.x-17, p->hitbox.y-27};
            DrawTextureRec(sprite_r, recto, victor, WHITE);
        }
    }


}

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

void move_pad_player(Player* p){
    if(IsGamepadButtonDown(0,GAMEPAD_BUTTON_LEFT_FACE_UP) && p->side[0] != 3 && p->side[1] != 3) p->hitbox.y -= p->speed;
    if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) && p->side[0] != 1 && p->side[1] != 1) p->hitbox.y += p->speed;
    if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) && p->side[0] != 2 && p->side[1] != 2) p->hitbox.x -= p->speed;
    if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) && p->side[0] != 4 && p->side[1] != 4) p->hitbox.x += p->speed;

    if(IsGamepadButtonDown(0,GAMEPAD_BUTTON_LEFT_FACE_UP)) p->facing = 1;
    if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) p->facing = 3;
    if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) p->facing = 2;
    if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) p->facing = 4;
}

void ataque_player(Player* p){
    if(IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_LEFT) && !p->timer_atack){
        p->timer_atack = FPS * 1.5;
    }

    if(IsKeyPressed(KEY_SPACE) && !p->timer_atack){
        p->timer_atack = FPS * 1.5;
    }

    if(p->timer_atack)
        p->timer_atack--;

    if(p->timer_damage)
        p->timer_damage--;
}

void use_awas(Player* p){
    int use = IsKeyDown(KEY_LEFT_SHIFT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);

    if( use && !p->timer_awas && list_size(p->awas)){
        AwasdeSabor* a = list_pop(p->awas);
        p->timer_damage += FPS / 2;
        p->timer_atack += FPS / 2;

        switch (a->sabor) {
            case 1:
                if(p->vida < p->max_vida)
                    p->vida = p->max_vida;
                else
                    p->vida ++;
                p->timer_awas += FPS;
                break;
            case 2:
                p->speed += velocidad(2.5f);
                p->timer_awas += FPS * 6;
                break;
            case 3:
                p->damage += 2;
                p->timer_awas += FPS * 5;
                break;
            case 4:
                p->timer_awas += FPS;
                if(p->vida < p->max_vida-1)
                    p->vida += 1;
                else if (p->vida == p->max_vida-1)
                    p->vida += 2;
                else
                    p->vida += 3;
                break;
        }

        free(a);
        p->vida = p->vida > 10? 10: p->vida;

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

    if(IsGamepadAvailable(0))
        move_pad_player(p);
    else
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

    //cosas de manage
void chocar_paredes(Player* p, List* w) {

    int side = 0;

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

        if(side==1)
            p->hitbox.y = p->hitbox.y - (SIZE - dif_y) +2;
        if(side==2)
            p->hitbox.x = p->hitbox.x + (SIZE - dif_x);
        if(side==3)
            p->hitbox.y = p->hitbox.y + (SIZE - dif_y);
        if(side==4)
            p->hitbox.x = p->hitbox.x - (SIZE - dif_x) +2;

        if (p->side[0] == 0)
            p->side[0] = side;
        else
            p->side[1] = side;
    }
}


//ENEMIGOS
void asign_stats(Enemy* e){
    float r = (float)(rand()%7 -3)/10;
    float r_2 = (float)(rand()%7 -3)/10;

    switch (e->type) {
        case 1:     //Base
            e->vida = 4;
            e->speed = velocidad(2.6f + r);
            e->damage = 1;
            e->vision = 4 + r_2;
            break;
        case 2:     //Tanque agresivo
            e->vida = 7;
            e->speed = velocidad(1 + r);
            e->damage = 2;
            e->vision = 6 + r_2;
            break;
        case 3:    //Pequeño que se multiplica
            e->vida = 2;
            e->speed = velocidad(2.2f + r * 3);
            e->damage = 1;
            e->vision = 4.5f + r_2;
            e->timer_extra = 0;
            break;
        case 4:     //Mímico
            e->vida = 3;
            e->speed = velocidad(3 + r);
            e->damage = 2;
            e->vision = 1 + r_2;
            break;
        case 5:     //timido
            e->vida = 4;
            e->speed = velocidad(2.8f + r);
            e->damage = 1;
            e->vision = 6.5f + r_2;
            break;
        default:
            e->vida = 1;
            e->speed = 0;
            e->damage = 0;
            e->vision = 0;
    }
}

List* summon_enemies(int map[64][64]){
    List* l = new_list();

    for (int i = 0; i < 64; ++i) {      // i = y
        for (int j = 0; j < 64; ++j) {      //j = x
            if(map[i][j] == FLOOR_SPAWN){
                Enemy* e = malloc(sizeof(Enemy));
                e->type = rand()%5 + 1;
                e->hitbox = create_hitbox((float)j * SIZE, (float)i * SIZE);
                e->timer = 0;
                e->facing = rand()%2 + 1;
                asign_stats(e);
                list_add(l,e);

            }
        }
    }

    return l;
}

void draw_enemies(List* l, Texture2D sprite){
    for (int i = 0; i < list_size(l); ++i) {
        Enemy* e = list_get(l, i);

        Rectangle r = {SIZE * (e->facing - 1) * 3,SIZE * (e->type - 1) * 2,SIZE * 3,SIZE * 2};
        Vector2 v = {e->hitbox.x - SIZE, e->hitbox.y - SIZE};

        if(e->timer % 16 > 8 || e->timer < 16)
            DrawTextureRec(sprite, r, v, WHITE);

    }
}
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

    float total = (movement_x * (float)dir_x) + (movement_y * (float)dir_y);

    movement_x = movement_x / total * e->speed;
    movement_y = movement_y / total * e->speed;

    float huida = 1;
    if(e->type == 5 && distance(p->hitbox, e->hitbox) < e->vision * 3 / 4 * SIZE){
        if(p->facing == 3 && dir_y < 0 && movement_y * (float)dir_y > movement_x * (float)dir_x)
            huida *= -0.75f;
        if(p->facing == 1 && dir_y > 0 && movement_y * (float)dir_y >= movement_x * (float)dir_x)
            huida *= -0.75f;
        if(p->facing == 2 && dir_x < 0 && movement_x * (float)dir_x > movement_x * (float)dir_y)
            huida *= -0.75f;
        if(p->facing == 4 && dir_x > 0 && movement_x * (float)dir_x >= movement_x * (float)dir_y)
            huida *= -0.75f;
    }

    e->facing = dir_x > 0? 2: 1;

    e->hitbox.x += movement_x * huida;
    e->hitbox.y += movement_y * huida;

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
        p->timer_damage += (int)(FPS * 1.5);
        p->vida -= e->damage;
    }


}


//ENEMIGOS ESPECIALES

Enemy* pequeno(Player* p, Enemy* e){
    if(distance(p->hitbox, e->hitbox) > (e->vision + 1) * 1.5 * SIZE){
        e->timer_extra = 0;
        return NULL;
    }

    if(!e->timer_extra) {
        e->timer_extra = FPS * 8 + 1;
        return NULL;
    }

    e->timer_extra --;

    if(e->timer_extra == 1){
        Enemy* e_2 = malloc(sizeof(Enemy));
        e_2->type = 3;
        e_2->hitbox = create_hitbox(e->hitbox.x, e->hitbox.y);
        e_2->timer = 0;
        e_2->facing = rand()%2 + 1;
        asign_stats(e_2);
        return e_2;
    }


    return NULL;
}

void mimico(Player* p, Enemy* e){
    if(distance(p->hitbox, e->hitbox) > (e->vision + 1) * SIZE)
        e->vision = 1;
    else
        e->vision = 3.5f;
}

int manage_enemies(Player* p, List* l, List* a){

    for(int i = 0; i < list_size(l); i++){
        Enemy* e = list_get(l,i);

        if(e->type == 3) {
            Enemy* e_2 = pequeno(p, e);
            if (e_2)
                list_add(l, e_2);
        }
        if(e->type == 4)
            mimico(p, e);

        move_enemies(p, e);
        lastimar_atacar(p, e);

        if(e->vida <= 0) {
            if(e->type == 4 || rand()% 6 < 1)
                drop_awa(a, e->hitbox);

            printf("Lo vamoa matar \n");
            list_delete(l, i);
            printf("Ha morido\n");
            break;
        }
    }

    if(list_size(l))
        return 0;
    else
        return 1;
}


//CAMARA
Camera2D crear_camara(Player* p){
    Camera2D c;
    c.zoom = 48.0f / SIZE;    // El primer número es el tamaño mostrado en pixeles de size
    c.rotation = 0;
    c.offset = (Vector2){S_WIDHT/2.0 - (SIZE-2)/2.0 * c.zoom , S_HEIGHT/2.0 - (SIZE-2)/2.0 * c.zoom};
    update_camara(p, &c);

    return c;
}

void update_camara(Player* p, Camera2D* c){
    c->target = (Vector2){p->hitbox.x,p->hitbox.y};
}




