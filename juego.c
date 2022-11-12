
#include "juego.h"
#include "global.h"

struct player{
    Rectangle hitbox;
    int vidas;
    //sprite
    //Rectangle
};

Player* create_player(){
    Player* jugador = malloc(sizeof(Player));
    jugador->hitbox = create_hitbox(S_WIDHT/3.0,S_HEIGHT/2.0);
    jugador->vidas = 3;
    return jugador;
}