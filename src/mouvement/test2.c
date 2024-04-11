#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <unistd.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 800
#define SPRITE_WIDTH 200 // Nouvelle largeur de l'image
#define SPRITE_HEIGHT 150 // Nouvelle hauteur de l'image

#define BOARD_SIZE_X 24
#define BOARD_SIZE_Y 24

#define NB_MAP_X 2
#define NB_MAP_Y 1

// Calcul de la taille des cases du plateau en fonction de la taille de la fenêtre
#define CELL_WIDTH (WINDOW_WIDTH / BOARD_SIZE_X)
#define CELL_HEIGHT (WINDOW_HEIGHT / BOARD_SIZE_Y)

#define FRAME_DROITE 8
#define FRAME_GAUCHE 9
#define FRAME_HAUT 10
#define FRAME_BAS 11
#define TAILLE_SPRITE 65

#define NB_AREA 8
#define FRAME_WALK 0
#define STONE -1
#define TREE -2
#define CRYSTALL -3
#define CACTUS -4
#define WATER -5
#define DOOR_O -6
#define DOOR_C -7

#define SORTIE -9999

typedef struct img_s{
    int nb_sprite;
    int num_ref;
    SDL_Rect **texture;
}img_t;

typedef enum{
    WALK_R,
    WALK_L,
    WALK_U,
    WALK_D,
    INTERACT,
    HIDE,
    IDLE
}state_t;

typedef enum{
    DOWN,
    RIGHT,
    LEFT,
    UP
    
}direction_t;

typedef struct{
    int x;
    int y;
    direction_t direction;
    state_t state;
    SDL_Texture *Texture;
    img_t **sprite_move;
    SDL_Rect *position;
}personnage_t;


typedef struct{
    int x;
    int y;
    int map[NB_MAP_Y][NB_MAP_X][24][24];
}map_t;

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



SDL_Texture** load_area(SDL_Renderer **render) {
    SDL_Surface **Surface = malloc(sizeof(SDL_Surface *) * NB_AREA);
    if (Surface == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour les surfaces.\n");
        return NULL;
    }

    char path[40];
    for (int i = 0; i < NB_AREA; i++) {
        sprintf(path, "image/area/%d.png", i); // Utilisation de sprintf pour concaténer les chaînes de caractères
        Surface[i] = IMG_Load(path);
        if (Surface[i] == NULL) {
            printf("Erreur lors du chargement de l'image : %s\n", SDL_GetError());
            for (int j = 0; j < i; j++) {
                SDL_FreeSurface(Surface[j]); // Libérer les surfaces déjà chargées
            }
            free(Surface); // Libérer la mémoire allouée pour les surfaces
            return NULL;
        }
    }

    SDL_Texture **area = malloc(sizeof(SDL_Texture *) * NB_AREA);
    if (area == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour les textures.\n");
        for (int i = 0; i < NB_AREA; i++) {
            SDL_FreeSurface(Surface[i]); // Libérer les surfaces déjà chargées
        }
        free(Surface); // Libérer la mémoire allouée pour les surfaces
        return NULL;
    }

    for (int i = 0; i < NB_AREA; i++) {
        area[i] = SDL_CreateTextureFromSurface(*render, Surface[i]);
        if (area[i] == NULL) {
            printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
            for (int j = 0; j < i; j++) {
                SDL_DestroyTexture(area[j]); // Libérer les textures déjà créées
            }
            free(area); // Libérer la mémoire allouée pour les textures
            for (int j = 0; j < NB_AREA; j++) {
                SDL_FreeSurface(Surface[j]); // Libérer les surfaces déjà chargées
            }
            free(Surface); // Libérer la mémoire allouée pour les surfaces
            return NULL;
        }
    }

    for (int i = 0; i < 4; i++) {
        SDL_FreeSurface(Surface[i]); // Libérer les surfaces maintenant que les textures ont été créées
    }
    free(Surface); // Libérer la mémoire allouée pour les surfaces

    return area;
}


int rending(SDL_Renderer **render,personnage_t *perso,int map[24][24],SDL_Texture **area){
    SDL_RenderClear(*render); // Effacer le rendu précédent
    // Dessiner le plateau
    for(int i=0;i<BOARD_SIZE_Y;i++){
            for(int j=0;j<BOARD_SIZE_X;j++){
                SDL_Rect rect = {j * CELL_WIDTH, i * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT};
                SDL_RenderCopy(*render, area[0], NULL, &rect);
                SDL_RenderCopy(*render, area[abs(map[i][j])], NULL, &rect);

            }
        }
    // Dessiner le personnage
    perso->position->y = (perso->y * (WINDOW_HEIGHT / BOARD_SIZE_Y)) % WINDOW_HEIGHT;
    perso->position->x = (perso->x * (WINDOW_WIDTH / BOARD_SIZE_X)) % WINDOW_WIDTH;
    SDL_RenderCopy(*render, perso->Texture, perso->sprite_move[perso->direction]->texture[perso->sprite_move[perso->direction]->num_ref], perso->position);
    SDL_RenderPresent(*render);
    return 0;
}

int build_board(int (*board)[24][24],int value,int x,int y){
    printf("%d\n",(*board)[y][x]);
    (*board)[y][x] = -value;
    return 0;
}

int import_board(int (*board)[24][24],char *path){
    FILE *file = fopen(path,"r");
    if(file == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }
    for(int i=0;i<24;i++){
        for(int j=0;j<24;j++){
            fscanf(file,"%d",&(*board)[i][j]);
        }
    }
    fclose(file);
    return 0;
}

int export_board(int (*board)[24][24],char *path){
    FILE *file = fopen(path,"w");
    if(file == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }
    for(int i=0;i<24;i++){
        for(int j=0;j<24;j++){
            fprintf(file,"%d ",(*board)[i][j]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}

int free_personnage(personnage_t **perso){
    for(int i=0;i<4;i++){
        for(int j=0;j<9;j++){
            free((*perso)->sprite_move[i]->texture[j]);
        }
        free((*perso)->sprite_move[i]->texture);
        free((*perso)->sprite_move[i]);
    }
    free((*perso)->sprite_move);
    free((*perso)->position);
    free((*perso));
    return 0;
}

int free_area(SDL_Texture ***area){
    for(int i=0;i<NB_AREA;i++){
        SDL_DestroyTexture((*area)[i]);
    }
    free(*area);
    return 0;
}

int pose_block(int (*board)[24][24],int key,int x,int y){
    int id=key-SDLK_0;
    printf("%d\n",id);
    if(id>=0 && id<=NB_AREA){
        build_board(board,id,x,y);
    }
    else{
        printf("Invalid key\n");
    }
    
    return 0;
}

int interact(map_t *map,int x,int y,int direction){
    int num_map_x = (map)->x;
    int num_map_y = (map)->y;
    if((map)->map[num_map_y][num_map_x][y][x] == DOOR_O){
        (map)->map[num_map_y][num_map_x][y][x] = DOOR_C;
    }
    else if((map)->map[num_map_y][num_map_x][y][x] == DOOR_C){
        (map)->map[num_map_y][num_map_x][y][x] = DOOR_O;
    }
    else if((map)->map[num_map_y][num_map_x][y][x]==SORTIE){
        /*PRENDRE EN COMPTE DIRECTION ET XMAP,YMAP POUR LES DEP*/
    }

    return 0;
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
    
    import_board(&map.map[map.x][map.y],"board.txt");
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
                        if(map.map[map.x][map.y][perso->y][(perso->x+1)%BOARD_SIZE_X] == 0 || map.map[map.x][map.y][perso->y][(perso->x+1)%BOARD_SIZE_X] == DOOR_O){
                            perso->x = (perso->x+1)%BOARD_SIZE_X;
                            
                        }
                        else{
                            printf("%d\n",map.map[map.x][map.y][perso->y][(perso->x+1)%BOARD_SIZE_X]);
                            printf("You can't go there\n");
                        }
                    perso->state = WALK_R;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    perso->direction = LEFT;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_L?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_L)
                        if(map.map[map.x][map.y][perso->y][(perso->x-1 + BOARD_SIZE_X)%BOARD_SIZE_X] == 0 || map.map[map.x][map.y][perso->y][(perso->x-1 + BOARD_SIZE_X)%BOARD_SIZE_X] == DOOR_O ){
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
                        if(map.map[map.x][map.y][(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y][perso->x] == 0 || map.map[map.x][map.y][(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y][perso->x] == DOOR_O ){
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
                        if(map.map[map.x][map.y][(perso->y+1)%BOARD_SIZE_Y][perso->x] == 0 || map.map[map.x][map.y][(perso->y+1)%BOARD_SIZE_Y][perso->x] == DOOR_O){
                            perso->y = (perso->y+1)%BOARD_SIZE_Y;
                        }
                        else{
                            printf("You can't go there\n");
                        }
                    perso->state = WALK_D;
                }
                
                else if (event.key.keysym.sym == SDLK_e) {
                    printf("Exportation du plateau\n");
                    export_board(&map.map[map.x][map.y],"board.txt");
                }
                else if (event.key.keysym.sym == SDLK_r) {
                    printf("Reset du plateau\n");
                    import_board(&map.map[map.x][map.y],"board.txt");
                }
                else if (event.key.keysym.sym == SDLK_a) {
                    printf("Clear du plateau\n");
                    for(int i=0;i<24;i++){
                        for(int j=0;j<24;j++){
                            map.map[map.x][map.y][i][j] = 0;
                        }
                    }
                }
                else if (event.key.keysym.sym == SDLK_q) {
                    if(perso->direction == RIGHT && perso->x+1<BOARD_SIZE_X)
                        interact(&map,(perso->x+1)%BOARD_SIZE_X,perso->y,perso->direction);
                    else if(perso->direction == LEFT && perso->x-1>=0)
                        interact(&map,(perso->x-1 + BOARD_SIZE_X)%BOARD_SIZE_X,perso->y,perso->direction);
                    else if(perso->direction == UP && perso->y-1>=0)
                        interact(&map,perso->x,(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y,perso->direction);
                    else if(perso->direction == DOWN && perso->y+1<BOARD_SIZE_Y)
                        interact(&map,perso->x,(perso->y+1 + BOARD_SIZE_Y)%BOARD_SIZE_Y,perso->direction);
                }
                else{
                    if(perso->direction == RIGHT && perso->x+1<BOARD_SIZE_X)
                        pose_block(&map.map[map.x][map.y],event.key.keysym.sym,(perso->x+1)%BOARD_SIZE_X,perso->y);
                    else if(perso->direction == LEFT && perso->x-1>=0)
                        pose_block(&map.map[map.x][map.y],event.key.keysym.sym,(perso->x-1 + BOARD_SIZE_X)%BOARD_SIZE_X,perso->y);
                    else if(perso->direction == UP && perso->y-1>=0)
                        pose_block(&map.map[map.x][map.y],event.key.keysym.sym,perso->x,(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y);
                    else if(perso->direction == DOWN && perso->y+1<BOARD_SIZE_Y)
                        pose_block(&map.map[map.x][map.y],event.key.keysym.sym,perso->x,(perso->y+1 + BOARD_SIZE_Y)%BOARD_SIZE_Y);
                }
            }
    
        
        }
        rending(&renderer,perso,map.map[map.x][map.y],area);
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
