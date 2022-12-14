
#ifndef GAME_LIBRARBY_H
#define GAME_LIBRARBY_H

#include "global.h"

//Para simplificar
Rectangle create_hitbox(float x, float y);
Rectangle hitbox_arma(int lado, float x, float y);
float velocidad (float tiles);
float diferencia(float num_1, float num_2);
double distance(Rectangle point_1, Rectangle point_2);

//Funciones Listas
List* new_list();
void list_kill(List* l);

//Lista rara para recorrerse enteramente
void list_add(List* l, void* element);
void list_delete(List* l, int position);
void* list_get(List* l, int position);
int list_size(List* l);

//Stack
void* list_pop(List* l);
void* list_peek(List* l);


#endif //GAME_LIBRARBY_H
