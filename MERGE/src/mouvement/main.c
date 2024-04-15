#include "../include/common/board.h"





int main() {  
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("SDL Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return -1;
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        return -1;
    }

    // Initialisation de SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        return -1;
    }

    perso *perso=malloc(sizeof(perso));
    init_perso(perso, "tata", 1,1,1,1,1,1, 1, LEFT, &renderer);
    display_perso(*perso);
    import(perso);
    display_perso(*perso);
    

    SDL_Texture **area = load_area(&renderer);
    // Boucle principale
    int running = 1;
    SDL_Event event;
    map_t map;
    map.x = 0;
    map.y = 0;
    map.path[0][0] = malloc(sizeof(char)*20);
    strcpy(map.path[0][0],"data/map/board.txt");
    
    map.path[0][1] = malloc(sizeof(char)*20);
    strcpy(map.path[0][1],"data/map/board2.txt");
    
    
    import_board(&map.map[map.y][map.x],map.path[map.y][map.x]);
    
    SDL_Surface *SurfaceOut = IMG_Load("data/image/area/OUT.png");
    SDL_Texture *TextureOut = SDL_CreateTextureFromSurface(renderer, SurfaceOut);
    SDL_FreeSurface(SurfaceOut);

    npc_s *npc = npc_creator("toto", "toto", 10, "data/image/perso.png", LEFT, &renderer, 0);
    npc_s *npc2 = npc_creator("kevin", "Je etre kevin", 10, "data/image/perso.png", LEFT, &renderer, 0);

    game_s *g = malloc(sizeof(game_s));
    game_init_game(g,&map,TextureOut,area);
    game_add_main_perso(g,perso);
    game_add_npc(g,npc);
    game_add_npc(g,npc2);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                export_board(&map.map[map.y][map.x],map.path[map.y][map.x]);
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    perso->direction = RIGHT;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_R?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_R){
                    
                        if((perso->x+1>=0 && perso->x+1<BOARD_SIZE_X) && collision(&map.map[map.y][map.x],perso->x+1,perso->y)){
                            perso->x = (perso->x+1)%BOARD_SIZE_X;
                            
                        }
                        else{
                            printf("%d\n",map.map[map.y][map.x][perso->y][(perso->x+1)%BOARD_SIZE_X]);
                            printf("You can't go there\n");
                        }
                    }
                    perso->state = WALK_R;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    perso->direction = LEFT;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_L?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_L){
                        if((perso->x-1>=0 && perso->x-1<BOARD_SIZE_X) && collision(&map.map[map.y][map.x],perso->x-1,perso->y)){
                            perso->x = (perso->x-1)%BOARD_SIZE_X;
                        }else{
                            printf("You can't go there\n");
                        }
                    }
                    perso->state = WALK_L;
                }
                else if (event.key.keysym.sym == SDLK_UP) {
                    perso->direction = UP;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_U?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_U){
                        if((perso->y-1>=0 && perso->y-1<BOARD_SIZE_Y) && collision(&map.map[map.y][map.x],perso->x,perso->y-1) ){
                            perso->y = (perso->y-1)%BOARD_SIZE_Y;
                        }
                        else{
                            printf("You can't go there\n");
                        }
                        }
                    perso->state = WALK_U;
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    perso->direction = DOWN;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_D?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_D){
                        if((perso->y+1>=0 && perso->y+1<BOARD_SIZE_Y) && collision(&map.map[map.y][map.x],perso->x,perso->y+1)){
                            perso->y = (perso->y+1)%BOARD_SIZE_Y;
                        }
                        else{
                            printf("You can't go there\n");
                        }
                    }
                    perso->state = WALK_D;
                }
                
                else if (event.key.keysym.sym == SDLK_e) {
                    printf("Exportation du plateau\n");
                    export_board(&map.map[map.y][map.x],map.path[map.y][map.x]);
                }
                else if (event.key.keysym.sym == SDLK_r) {
                    printf("Reset du plateau\n");
                    import_board(&map.map[map.y][map.x],map.path[map.y][map.x]);
                }
                else if (event.key.keysym.sym == SDLK_a) {
                    printf("Clear du plateau\n");
                    for(int i=0;i<24;i++){
                        for(int j=0;j<24;j++){
                            map.map[map.y][map.x][i][j] = 0;
                        }
                    }
                }
                else if (event.key.keysym.sym == SDLK_q) {
                    if(perso->direction == RIGHT && perso->x+1<BOARD_SIZE_X)
                        interact(g,(perso->x+1)%BOARD_SIZE_X,perso->y);
                    else if(perso->direction == LEFT && perso->x-1>=0)
                        interact(g,(perso->x-1)%BOARD_SIZE_X,perso->y);
                    else if(perso->direction == UP && perso->y-1>=0)
                        interact(g,perso->x,(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y);
                    else if(perso->direction == DOWN && perso->y+1<BOARD_SIZE_Y)
                        interact(g,perso->x,(perso->y+1 + BOARD_SIZE_Y)%BOARD_SIZE_Y);
                }
                else{
                    if(perso->direction == RIGHT && perso->x+1<BOARD_SIZE_X)
                        pose_block(&map.map[map.y][map.x],event.key.keysym.sym,(perso->x+1)%BOARD_SIZE_X,perso->y);
                    else if(perso->direction == LEFT && perso->x-1>=0)
                        pose_block(&map.map[map.y][map.x],event.key.keysym.sym,(perso->x-1 + BOARD_SIZE_X)%BOARD_SIZE_X,perso->y);
                    else if(perso->direction == UP && perso->y-1>=0)
                        pose_block(&map.map[map.y][map.x],event.key.keysym.sym,perso->x,(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y);
                    else if(perso->direction == DOWN && perso->y+1<BOARD_SIZE_Y)
                        pose_block(&map.map[map.y][map.x],event.key.keysym.sym,perso->x,(perso->y+1 + BOARD_SIZE_Y)%BOARD_SIZE_Y);
                }
            }
    
        
        }
        
        rending(&renderer,g);
    }
    // Libération de la mémoire
    export(perso);
    game_destroy_game(&g);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
   

    return 0;
    
}
