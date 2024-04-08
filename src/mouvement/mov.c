#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <unistd.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SPRITE_WIDTH 200 // Nouvelle largeur de l'image
#define SPRITE_HEIGHT 150 // Nouvelle hauteur de l'image

typedef struct img_s{
    char *ref;
    int nb_sprite;
    SDL_Texture **texture;
}img_t;

typedef enum{
    WALK_R,
    WALK_L,
    INTERACT,
    HIDE,
    IDLE
}state_t;

int main(int argc, char *argv[]) {    
    int nb_sprite = 9;
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

    // Chargement des images
    img_t walk;
    img_t interact;
    img_t hide;
    img_t idle;
    walk.ref = "image/walk/";
    walk.nb_sprite = 9;

    interact.ref = "image/interact/";
    interact.nb_sprite = 3;

    hide.ref = "image/hide/";
    hide.nb_sprite = 11;

    idle.ref = "image/idle/";
    idle.nb_sprite = 5;

    
    walk.texture = malloc(walk.nb_sprite * sizeof(SDL_Texture *));
    for(int i=1; i<=walk.nb_sprite; i++){
        char path[100];
        sprintf(path, "%s%d.png", walk.ref, i);
        walk.texture[i-1] = IMG_LoadTexture(renderer, path);
        if (walk.texture[i-1] == NULL) {
            printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
            return -1;
        }
    }

    interact.texture = malloc(interact.nb_sprite * sizeof(SDL_Texture *));
    for(int i=1; i<=interact.nb_sprite; i++){
        char path[100];
        sprintf(path, "%s%d.png", interact.ref, i);
        interact.texture[i-1] = IMG_LoadTexture(renderer, path);
        if (interact.texture[i-1] == NULL) {
            printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
            return -1;
        }
    }

    hide.texture = malloc(hide.nb_sprite * sizeof(SDL_Texture *));
    for(int i=1; i<=hide.nb_sprite; i++){
        char path[100];
        sprintf(path, "%s%d.png", hide.ref, i);
        hide.texture[i-1] = IMG_LoadTexture(renderer, path);
        if (hide.texture[i-1] == NULL) {
            printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
            return -1;
        }
    }

    idle.texture = malloc(idle.nb_sprite * sizeof(SDL_Texture *));
    for(int i=1; i<=idle.nb_sprite; i++){
        char path[100];
        sprintf(path, "%s%d.png", idle.ref, i);
        idle.texture[i-1] = IMG_LoadTexture(renderer, path);
        if (idle.texture[i-1] == NULL) {
            printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
            return -1;
        }
    }

    // Boucle principale
    int running = 1;
    int walk_ref = 0;
    int idling = 0;
    int hide_ref = 0;
    int interact_ref = 0;
    SDL_Event event;
    int x = (WINDOW_WIDTH - SPRITE_WIDTH) / 2;
    int y = (WINDOW_HEIGHT - SPRITE_HEIGHT) / 2;
    state_t state = IDLE;
    SDL_Rect destinationRect = {x, y, SPRITE_WIDTH, SPRITE_HEIGHT};
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    state = WALK_R;
                    walk_ref = (walk_ref + 1) % walk.nb_sprite;
                    destinationRect.x = (destinationRect.x + 10) % WINDOW_WIDTH;
                    
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    state = WALK_L;
                    walk_ref = (walk_ref - 1 + nb_sprite) % walk.nb_sprite;
                    destinationRect.x = (destinationRect.x - 10 + WINDOW_WIDTH) % WINDOW_WIDTH;
                }
                else if (event.key.keysym.sym == SDLK_UP) {
                    state = INTERACT;
                    
                    for(int i=0;i<interact.nb_sprite;i++){
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer,*(interact.texture+i) , NULL, &destinationRect);
                        SDL_RenderPresent(renderer);
                        usleep(55000);
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
                    state = IDLE;
                }
            }
            
            
        }
        
        // Effacement de l'écran
        

        // Calcul des coordonnées de destination pour centrer l'image
        
        
        SDL_RenderClear(renderer);
        // Affichage de l'image avec la taille redimensionnée
        printf("state : %d\n", state);
        switch (state)
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
        

        // Actualisation de l'affichage
        SDL_RenderPresent(renderer);
        
        usleep(55000); // Pour ralentir le changement d'image
    }

    // Libération de la mémoire
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
