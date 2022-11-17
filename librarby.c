
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

float diferencia(float num_1, float num_2){
    float dif = num_1 - num_2;
    dif = dif < 0? dif * -1: dif;
    return dif;
}




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
    l->elements--;
    if(l->elements <= 0)
        return;
    l->array[position] = l->array[l->elements];
    l->array[l->elements] = NULL;

}

void* list_get(List* l, int position){
    return l->array[position];
}

int list_size(List* l){
    return l->elements;
}

void* list_pop(List* l){
    if(l->elements <= 0)
        return NULL;
    l->elements--;
    void* a = l->array[l->elements];
    l->array[l->elements] = NULL;
    return a;
}

void* list_peek(List* l){
    if(l->elements <= 0)
        return NULL;
    return l->array[l->elements-1];
}
