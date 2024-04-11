#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <unistd.h>

#define WINDOW_WIDTH 1900
#define WINDOW_HEIGHT 1080
#define SPRITE_WIDTH 200 // Nouvelle largeur de l'image
#define SPRITE_HEIGHT 150 // Nouvelle hauteur de l'image

#define BOARD_SIZE_X 24
#define BOARD_SIZE_Y 24

// Calcul de la taille des cases du plateau en fonction de la taille de la fenêtre
#define CELL_WIDTH (WINDOW_WIDTH / BOARD_SIZE_X)
#define CELL_HEIGHT (WINDOW_HEIGHT / BOARD_SIZE_Y)

#define FRAME_DROITE 8
#define FRAME_GAUCHE 9
#define FRAME_HAUT 10
#define FRAME_BAS 11
#define TAILLE_SPRITE 65
typedef struct img_s{
    int nb_sprite;
    int num_ref;
    SDL_Rect *texture;
}img_t;

typedef enum{
    WALK_R,
    WALK_L,
    INTERACT,
    HIDE,
    IDLE
}state_t;

typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT
}direction_t;

typedef struct{
    int x;
    int y;
    direction_t direction;
    state_t state;
    SDL_Texture *Texture;
    img_t **sprite_move;
    SDL_Rect position;
}personnage_t;

/*

int rending(SDL_Renderer *renderer,int board[BOARD_SIZE_Y][BOARD_SIZE_X],personnage_t *perso){
    SDL_RenderClear(renderer);
    for(int i=0;i<BOARD_SIZE_Y;i++){
        for(int j=0;j<BOARD_SIZE_X;j++){
            SDL_Rect rect = {j * CELL_WIDTH, i * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT};
            switch(board[i][j]){
                case 0:
                    SDL_RenderCopy(renderer,back , NULL, &rect);
                    break;
                case -1:
                    SDL_RenderCopy(renderer,stone , NULL, &rect);
                    break;
            }
        }
    }

    switch (perso->state)
        {
            case IDLE:
                SDL_RenderCopy(renderer,*(idle.texture+idling) , NULL, &destinationRect);
                break;
            case WALK_R:
                SDL_RenderCopy(renderer,*(walk.texture+walk_ref) , NULL, &destinationRect);
                break;
            case WALK_L:
                SDL_RenderCopyEx(renderer,*(walk.texture+walk_ref) , NULL, &destinationRect,180,NULL,SDL_FLIP_VERTICAL);
                break;
            case INTERACT:
                
                break;
            case HIDE:
                break;
            default:
                break;
        }
    SDL_RenderPresent(renderer);
    return 0;
}
   */
personnage_t * init_personnage(int x,int y,direction_t direction,SDL_Renderer **render){
    personnage_t *perso = malloc(sizeof(personnage_t));
    SDL_Surface * Surface =IMG_Load("image/perso.png"); 
    if(Surface == NULL) 
        printf("Erreur lors du chargement de l'image : %s\n",SDL_GetError());
    perso->Texture = malloc(sizeof(SDL_Texture));
    perso->Texture = SDL_CreateTextureFromSurface(render,Surface);

    if(perso->Texture == NULL) 
        printf("Erreur lors du chargement de l'image : %s\n",SDL_GetError());
    
    
    SDL_FreeSurface(Surface);
    perso->x = x;
    perso->y = y;
    perso->direction = direction;
    perso->state = IDLE;
    perso->sprite_move = malloc(sizeof(img_t *)*4);
    for(int i=0;i<4;i++){
        perso->sprite_move[i] = malloc(sizeof(img_t));
        perso->sprite_move[i]->texture = malloc(sizeof(SDL_Rect *)*9);  
        perso->sprite_move[i]->num_ref=0;
        perso->sprite_move[i]->nb_sprite = 9;
    }
    direction_t dir[4] = {FRAME_HAUT,FRAME_BAS,FRAME_GAUCHE,FRAME_DROITE};
    for(int i=0;i<4;i++){
        for(int j = 0; j < 9;j++){
            perso->sprite_move[i]->texture[j].y = dir[i] * TAILLE_SPRITE;
            perso->sprite_move[i]->texture[j].x = j * TAILLE_SPRITE;             /*Récupère les différentes frames*/
            perso->sprite_move[i]->texture->w = CELL_WIDTH;                 /*Taille du perso*/
            perso->sprite_move[i]->texture->h = CELL_HEIGHT;              /*Taille du perso*/
            SDL_Log("free de la surface du perso %d",i);
        }
    }
    printf("I m out!! \n");

    perso->position.y = (perso->x * (WINDOW_WIDTH/BOARD_SIZE_Y)) % WINDOW_WIDTH;
    perso->position.x = (perso->y * (WINDOW_WIDTH/BOARD_SIZE_X)) % WINDOW_WIDTH;
    printf("Let s go!! \n");
    int etat = SDL_RenderCopy(*render,perso->Texture,&perso->sprite_move[0][0],&perso->position);  
    if(etat != 0)
        SDL_Log("Erreur lors de l'affichage à l'écran");
    printf("Show time!! \n");
    while (1)
    {
        SDL_RenderPresent(*render);
    }
    
    
    printf("Outch!! \n");
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


    

    // Boucle principale
    int running = 1;
   
    SDL_Event event;
    int board[24][24]={
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1}};
    
    SDL_Texture *back = IMG_LoadTexture(renderer, "image/coll/back.png");

    personnage_t *perso = init_personnage(10,10,RIGHT,&renderer);

    /*
    while (running) {
        printf("pos_x : %d,pos_y:%d state %d\n", pos_x+1,pos_y+1,board[pos_y][pos_x]);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    walk_ref = state==WALK_R?((walk_ref + 1) % walk.nb_sprite):0;
                    state = WALK_R;
                    if(board[pos_y][(pos_x+1)%BOARD_SIZE_X] == 0){
                        pos_x = (pos_x+1)%BOARD_SIZE_X;
                        destinationRect.x = (pos_x * (WINDOW_WIDTH/BOARD_SIZE_X)) % WINDOW_WIDTH;
                    }
                    else{
                        printf("You can't go there\n");
                    }
                    
                    
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    walk_ref = state==WALK_L?((walk_ref + 1) % walk.nb_sprite):0;
                    state = WALK_L;
                    if(board[pos_y][(pos_x-1 + BOARD_SIZE_X)%BOARD_SIZE_X] == 0 ){
                        pos_x = (pos_x-1)%BOARD_SIZE_X;
                        destinationRect.x = (pos_x * (WINDOW_WIDTH/BOARD_SIZE_X)) % WINDOW_WIDTH;
                     }
                    else{
                        printf("You can't go there\n");
                    }
                }
                else if (event.key.keysym.sym == SDLK_UP) {
                    state = INTERACT;
                    
                    for(int i=0;i<interact.nb_sprite;i++){
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer,*(interact.texture+i) , NULL, &destinationRect);
                        SDL_RenderPresent(renderer);
                        usleep(55000);
                    }
                    if(board[(pos_y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y][pos_x] == 0 ){
                        pos_y = (pos_y-1)%BOARD_SIZE_Y;
                        destinationRect.y = (pos_y * (WINDOW_HEIGHT/BOARD_SIZE_Y)) % WINDOW_HEIGHT;
                     }
                    else{
                        printf("You can't go there\n");
                    }
                    state = IDLE;
                }
                else if (event.key.keysym.sym == SDLK_DOWN){
                    state = HIDE;
                    for(int i=0;i<4;i++){
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer,*(hide.texture+i) , NULL, &destinationRect);
                        SDL_RenderPresent(renderer);
                        usleep(55000);
                    }
                    event.type = SDL_KEYUP;
                    while(event.type!= SDL_KEYDOWN){
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer,*(hide.texture+4) , NULL, &destinationRect);
                        SDL_RenderPresent(renderer);
                        SDL_PollEvent(&event);
                    }
                    for(int i=5;i<hide.nb_sprite;i++){
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer,*(hide.texture+i) , NULL, &destinationRect);
                        SDL_RenderPresent(renderer);
                        usleep(55000);
                    }
                    if(board[(pos_y+1)%BOARD_SIZE_Y][pos_x] == 0 ){
                        pos_y = (pos_y+1)%BOARD_SIZE_Y;
                        destinationRect.y = (pos_y * (WINDOW_HEIGHT/BOARD_SIZE_Y)) % WINDOW_HEIGHT;
                     }
                    else{
                        printf("You can't go there\n");
                    }
                    state = IDLE;
                }
            }
        }
        
        // Effacement de l'écran
        

        // Calcul des coordonnées de destination pour centrer l'image
        
        
        SDL_RenderClear(renderer);
        // Affichage de l'image avec la taille redimensionnée
        rending(renderer,board,&destinationRect);
        
        

        // Actualisation de l'affichage
        SDL_RenderPresent(renderer);
        
        usleep(55000); // Pour ralentir le changement d'image
    }*/

    // Libération de la mémoire
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}





