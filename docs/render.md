Regresar al [readme](../README.md)

---

Esta parte del código es la encargada de renderizar en pantalla todo lo que está sucediendo, desde los mapas y el personaje en pantalla hasta los enemigos que se encuentran por el mapa.

## Mapa

Para renderizar el mapa, hablaremos de 2 funciones públicas que contiene ```map.h```: ```map_draw()``` y ```map_draw_bridges()```.

- ```void map_draw(int matrix[64][64], Texture2D sprite, int *temp)```:

    Esta función recibe como argumento la matriz 64x64 del mapa, el sprite en donde se encuentran las texturas y un apuntador a un entero que funcionará como timer para la animación del agua. Para empezar, analiza el valor del apuntador temp, para que cada 30 frames cambie la textura del agua, lo que crea la animación. Después, se recorre cada elemento de la matriz y dependiendo de su valor, va a dibujar la textura que le corresponda (Los valores están definidos en map.h, para más referencia visite [generación del mundo](./mapa.md))


- ```void map_draw_bridges(int matrix[64][64], Texture2D sprite, Texture2D sprite_b)```:

    Esta funciona exactamente de la misma manera que la anterior, pero le pasamos coomo argumento 2 sprites, uno que tiene las texturas de los puentes y el otro que tiene las texturas de las decoraciones, como estos elementos no tienen animación, no fue necesario incluir un timer

## Personajes

En esta categoría se dibujan a los enemigos y al personaje principal, para renderizar al personaje principal se llama a la función ```draw_player()``` y para dibujar a los enemigos se llama a ```draw_enemies()```.

- ```void draw_player(Player* p,Texture2D sprite, Texture2D hit, Texture2D sprite_r)```: 
    Esta función recibe las sprites del jugador (Depende de la dirección a la que se dirige) y la textura del ataque. Si el personaje está atacando en el momento en el que la función es llamada, se renderizará la textura de ataque en la dirección a la que esté volteando. La textura que tendrá el jugador, dependerá de su dirección, dando 4 posibles texturas por cada lado.

- ```void draw_enemies(List* l, Texture2D sprite):``` Esta función recibe la lista de todos los enemigos y el sprite en dónde se encuentra su respectiva textura para posteriormente a cada uno de ellos