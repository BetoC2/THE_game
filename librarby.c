
#include "librarby.h"

struct list{
    void** array;
    int elements;
    int size;
};

Rectangle create_hitbox(float x, float y){
    Rectangle r = {x, y, SIZE, SIZE};
    return r;
};

List* new_list(){
    List* l = malloc(sizeof(List));
    l->elements = 0;
    l->size = 4;
    l->array = calloc(l->size, sizeof(void*));

    return l;
}

void list_add(List* l, void* element){
    if(l->elements >= l->size){
        l->size *= 2;
        l->array = realloc(l->array, sizeof(void*) * l->size);
    }
    l->array[l->elements] = element;
    l->elements++;
}

void list_delete(List* l, int position){
    if(l->elements <= 0)
        return;
    l->array[position] = l->array[l->elements];
    l->array[l->elements] = NULL;
    l->elements--;
}

int list_size(List* l){
    return l->elements;
}




//Está de mientras, listas se están implementando

Walls* crear_paredes(){
    Walls* w = malloc(sizeof(Walls));
    w->size = 12;
    w->array = calloc(w->size, sizeof(Rectangle));
    w->array[0] = create_hitbox(2*SIZE, 6*SIZE);
    w->array[1] = create_hitbox(2*SIZE, 7*SIZE);
    w->array[2] = create_hitbox(2*SIZE, 8*SIZE);
    w->array[3] = create_hitbox(3*SIZE, 2*SIZE);
    w->array[4] = create_hitbox(8*SIZE, 1*SIZE);
    w->array[5] = create_hitbox(9*SIZE, 1*SIZE);
    w->array[6] = create_hitbox(10*SIZE, 2*SIZE);
    w->array[7] = create_hitbox(10*SIZE, 3*SIZE);
    w->array[8] = create_hitbox(8*SIZE, 5*SIZE);
    w->array[9] = create_hitbox(10*SIZE, 7*SIZE);
    w->array[10] = create_hitbox(12*SIZE, 7*SIZE);

    return w;
}

void draw_walls(Walls* w){
    for(int i = 0; i < w->size; i++){
        DrawRectangleRec(w->array[i], YELLOW);
    }
}
