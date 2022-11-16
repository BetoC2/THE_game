
#ifndef GAME_LIBRARBY_H
#define GAME_LIBRARBY_H

#include "global.h"

//Estructuras
typedef struct list List;

//Para simplificar
Rectangle create_hitbox(float x, float y);

//Funciones listas
List* new_list();
void list_add(List* l, void* element);
void list_delete(List* l, int position);
void* list_get(List* l, int position);
int list_size(List* l);



#endif //GAME_LIBRARBY_H
