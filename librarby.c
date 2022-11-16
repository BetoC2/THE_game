
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
