#include "../include/common/common.h"

personnage_t * init_personnage(int x,int y,direction_t direction,SDL_Renderer **render){
    
    personnage_t *perso = malloc(sizeof(personnage_t));
    SDL_Surface *Surface = IMG_Load("image/perso.png"); 
    if (Surface == NULL) {
        printf("Erreur lors du chargement de l'image : %s\n", SDL_GetError());
        return NULL; // Retourner NULL en cas d'échec du chargement de l'image
    }
    
    perso->Texture = SDL_CreateTextureFromSurface(*render, Surface);
    if (perso->Texture == NULL) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(Surface); // Libérer la surface si la création de la texture échoue
        free(perso); // Libérer la mémoire allouée pour le personnage
        return NULL;
    }

    SDL_FreeSurface(Surface);
    
    perso->x = x;
    perso->y = y;
    perso->direction = direction;
    perso->state = IDLE;
    perso->sprite_move = malloc(sizeof(img_t *)*4);
    for(int i=0;i<4;i++){
        perso->sprite_move[i] = malloc(sizeof(img_t *));
        perso->sprite_move[i]->texture = malloc(sizeof(SDL_Rect *)*9);  
        perso->sprite_move[i]->num_ref=0;
        perso->sprite_move[i]->nb_sprite = 9;
    }
    direction_t dir[4] = {FRAME_HAUT,FRAME_BAS,FRAME_GAUCHE,FRAME_DROITE};
    for(int ligne=0;ligne<4;ligne++){
        printf("Ligne : %d\n",ligne);
        for(int colonne = 0; colonne < 9;colonne++){
            printf("Colonne : %d\n",colonne);
            perso->sprite_move[ligne]->texture[colonne] = malloc(sizeof(SDL_Rect));
            perso->sprite_move[ligne]->texture[colonne]->y = dir[ligne] * TAILLE_SPRITE;
            perso->sprite_move[ligne]->texture[colonne]->x = colonne * TAILLE_SPRITE;             /*Récupère les différentes frames*/
            perso->sprite_move[ligne]->texture[colonne]->w = TAILLE_SPRITE;                 /*Taille du perso*/
            perso->sprite_move[ligne]->texture[colonne]->h = TAILLE_SPRITE;              /*Taille du perso*/
        }
    }
    perso->position = malloc(sizeof(SDL_Rect));
    perso->position->y = (perso->y * (WINDOW_HEIGHT / BOARD_SIZE_Y)) % WINDOW_HEIGHT;
    perso->position->x = (perso->x * (WINDOW_WIDTH / BOARD_SIZE_X)) % WINDOW_WIDTH;
    perso->position->w = CELL_WIDTH;
    perso->position->h = CELL_HEIGHT;

    SDL_RenderCopy(*render, perso->Texture, perso->sprite_move[0]->texture[0], perso->position);
    SDL_RenderPresent(*render);
    return perso;
}



int main(int argc, char *argv[]) {  
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

    personnage_t *perso = init_personnage(10, 10, RIGHT, &renderer);
    SDL_Texture **area = load_area(&renderer);
    // Boucle principale
    int running = 1;
    SDL_Event event;
    map_t map;
    map.x = 0;
    map.y = 0;
    map.path[0][0] = malloc(sizeof(char)*20);
    strcpy(map.path[0][0],"map/board.txt");
    
    map.path[0][1] = malloc(sizeof(char)*20);
    strcpy(map.path[0][1],"map/board2.txt");
    
    
    import_board(&map.map[map.y][map.x],map.path[map.y][map.x]);
    
    SDL_Surface *SurfaceOut = IMG_Load("image/area/OUT.png");
    SDL_Texture *TextureOut = SDL_CreateTextureFromSurface(renderer, SurfaceOut);
    SDL_FreeSurface(SurfaceOut);
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    perso->direction = RIGHT;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_R?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_R)
                    
                        if((perso->x+1>=0 && perso->x+1<BOARD_SIZE_X) && collision(&map.map[map.y][map.x],perso->x+1,perso->y)){
                            perso->x = (perso->x+1)%BOARD_SIZE_X;
                            
                        }
                        else{
                            printf("%d\n",map.map[map.y][map.x][perso->y][(perso->x+1)%BOARD_SIZE_X]);
                            printf("You can't go there\n");
                        }
                    perso->state = WALK_R;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    perso->direction = LEFT;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_L?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_L)
                        if((perso->x-1>=0 && perso->x-1<BOARD_SIZE_X) && collision(&map.map[map.y][map.x],perso->x-1,perso->y)){
                            perso->x = (perso->x-1)%BOARD_SIZE_X;
                        }else{
                            printf("You can't go there\n");
                        }
                    perso->state = WALK_L;
                }
                else if (event.key.keysym.sym == SDLK_UP) {
                    perso->direction = UP;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_U?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_U)
                        if((perso->y-1>=0 && perso->y-1<BOARD_SIZE_Y) && collision(&map.map[map.y][map.x],perso->x,perso->y-1) ){
                            perso->y = (perso->y-1)%BOARD_SIZE_Y;
                        }
                        else{
                            printf("You can't go there\n");
                        }
                    perso->state = WALK_U;
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    perso->direction = DOWN;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_D?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_D)
                        if((perso->y+1>=0 && perso->y+1<BOARD_SIZE_Y) && collision(&map.map[map.y][map.x],perso->x,perso->y+1)){
                            perso->y = (perso->y+1)%BOARD_SIZE_Y;
                        }
                        else{
                            printf("You can't go there\n");
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
                        interact(&map,(perso->x+1)%BOARD_SIZE_X,perso->y,perso->direction, perso);
                    else if(perso->direction == LEFT && perso->x-1>=0)
                        interact(&map,(perso->x-1 + BOARD_SIZE_X)%BOARD_SIZE_X,perso->y,perso->direction, perso);
                    else if(perso->direction == UP && perso->y-1>=0)
                        interact(&map,perso->x,(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y,perso->direction, perso);
                    else if(perso->direction == DOWN && perso->y+1<BOARD_SIZE_Y)
                        interact(&map,perso->x,(perso->y+1 + BOARD_SIZE_Y)%BOARD_SIZE_Y,perso->direction, perso);
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
        rending(&renderer,perso,map.map[map.y][map.x],area,TextureOut);
    }
    // Libération de la mémoire
    free_personnage(&perso);
    free_area(&area);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
    
}
