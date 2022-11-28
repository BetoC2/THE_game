
#include "juego.h"
#include "global.h"
#include "map.h"


int main(void)
{
    InitWindow(S_WIDHT, S_HEIGHT, "Coconut doggy");

    srand(time(NULL));
    SetTargetFPS(FPS);           // Poner el juego a 60 frames

    Texture2D sprite_w, sprite_d, sprite_p, sprite_decor, sprite_stats;
    sprite_w = LoadTexture("../assets/forest.png");
    sprite_d = LoadTexture("../assets/forestDecoration.png");
    sprite_p = LoadTexture("../assets/player.png");
    sprite_decor = LoadTexture("../assets/decoration.png");
    sprite_stats = LoadTexture("../assets/potis.png");

    //Creación del mapa al azar
    int map[64][64];
    int bridges[64][64];
    int water_temp = 0;
    Vector2 initial_position;
    map_generate(map, bridges, &initial_position);


    //Creación del jugador, enemigos y paredes
    Player* jugador = create_player(&initial_position);
    List* paredes = crate_walls(bridges);
    List* enemigos = summon_enemies(map);
    List* awas_tiradas = spawn_awas(&initial_position);
    Camera2D camara = crear_camara(jugador);


    int se_perdio;


    // YO SOY EL JUEGO :O
    while (!WindowShouldClose())    //Ver si se presiona esc o cierran la ventana
    {

        // Cambios
        update_camara(jugador, &camara);
        chocar_paredes( jugador, paredes);
        manage_awa(awas_tiradas, jugador);
        se_perdio = manage_player(jugador);
        if(manage_enemies(jugador, enemigos, awas_tiradas))
            break;

        if(se_perdio)
            break;



        BeginDrawing(); //---------------------
        BeginMode2D(camara);


        ClearBackground(WATER);

        map_draw(map,  sprite_w, &water_temp);
        map_draw_bridges(bridges, sprite_decor, sprite_d);
        draw_enemies(enemigos);
        draw_awa(awas_tiradas, sprite_stats);
        draw_player(jugador, sprite_p);
        draw_stats(jugador, sprite_stats , camara);


        EndMode2D();
        EndDrawing(); //-----------------------

    }

    CloseWindow();
    if(rand()%2 && se_perdio)
        OpenURL("https://www.youtube.com/watch?v=RmUWWVZw28E");
    else if(se_perdio)
        OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");

    return 0;
}
