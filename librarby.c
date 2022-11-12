
#include "librarby.h"

struct list{
    void** array;
    int max;
};

List* list_new(){
    List* l = malloc(sizeof(List));
    l->max = 8;
    l->array = calloc(l->max, sizeof(void*));
    return l;
}

int add_to_list(List* l, void* element){
    void** current = l->array;

    for(int i = 0; i < l->max; i++){
        if(!current) {
            *current = element;
            return i;
        }
        current++;
    }

    l->max = l->max * 2;
    l->array = realloc(l->array, sizeof(void*) * l->max);
    for(int i = l->max/2 + 1; i < l->max; i++)
        l->array[i] = NULL;

    l->array[l->max/2] = element;
    return l->max/2;
}

void delete_element(List* l, int position){
    l->array[position] = NULL;
}

Rectangle create_hitbox(float x, float y){
    Rectangle r = {x, y, SIZE, SIZE};
    return r;
};





