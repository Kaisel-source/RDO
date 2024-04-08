#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <math.h>

#define N 20
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 790;
const int BUTTON_SIZEx = SCREEN_WIDTH/N;
const int BUTTON_SIZEy = SCREEN_HEIGHT/N;

/**
 * @brief position + image d un espace defeni
 * 
 */
typedef struct {
    SDL_Rect rect;       // Rectangle définissant la position et la taille du bouton
    SDL_Texture* texture; // Texture du bouton (à générer avec SDL_CreateTextureFromSurface())
} Button;

/**
 * @brief colle une img sur un espace defini
 * 
 * @param renderer 
 * @param imageTexture 
 * @param buttonRect 
 */
void setButtonImage(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect) {
    SDL_RenderCopy(renderer, imageTexture, NULL, buttonRect);
}




/**
 * @brief retoune un espace defenie sous la forme d un rectangle 
 * 
 * @param bouttonx 
 * @param bouttony 
 * @return SDL_Rect 
 */
SDL_Rect getButtonRect(int bouttonx, int bouttony) {
    Button buttonRect;
    buttonRect.rect.x = bouttonx;
    buttonRect.rect.y = bouttony;
    buttonRect.rect.w = BUTTON_SIZEx;
    buttonRect.rect.h = BUTTON_SIZEy;
    
    return buttonRect.rect;
}

/**
 * @brief 
 * @param plateau
 */
void genere_0(int mat[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            mat[i][j]=0;
        }
    }
}




/**
 * @brief fait le dessin d un echequier
 * 
 * @param plateau_de_combat 
 * @param gridX 
 * @param gridY 
 * @param rien 
 * @param buttonRect 
 * @param renderer 
 */
void dessin_map(int mat[N][N],Button buttonRect,SDL_Renderer* renderer,SDL_Texture * bloc_h,SDL_Texture * bloc_T,SDL_Texture * bloc_v){
    for (int row = 0; row < N; row++) {
        for (int column = 0; column < N; column++) {
            // Calcul de la position du bouton dans la grille
            int buttonX = column * BUTTON_SIZEx;
            int buttonY = row * BUTTON_SIZEy;
            // Dessiner le rectangle du bouton
            buttonRect.rect.x =  buttonX;   
            buttonRect.rect.y =  buttonY;
            buttonRect.rect.w =  BUTTON_SIZEx;
            buttonRect.rect.h = BUTTON_SIZEy;
            if(mat[row][column]==0){
                setButtonImage(renderer,bloc_h,&buttonRect.rect);
            }if(mat[row][column]==1){
                setButtonImage(renderer,bloc_T,&buttonRect.rect);
            }if(mat[row][column]==2){
                setButtonImage(renderer,bloc_v,&buttonRect.rect);
            }

        }
    } 
}


int main(){

    Button bouton1;

     //creation de fenetre 
    SDL_Window* window = SDL_CreateWindow("RDO TEST",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Création d'un renderer pour dessiner dans la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //charge le fond
    SDL_Surface* backgroundSurface = IMG_Load("../img/Wallhaven.png");
    if (backgroundSurface == NULL) {
        printf("Erreur de chargement de l'image de fond : %s\n", IMG_GetError());
        return 1;
    }


    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // initialise les image
    SDL_Surface* bloc = IMG_Load("../img/image.png");
    if (bloc == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface*  bloc1 = IMG_Load("../img/fondinter.png");
    if (bloc1 == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* bloc2 = IMG_Load("../img/test.png");
    if (bloc2 == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* bloc_h = SDL_CreateTextureFromSurface(renderer, bloc);
    SDL_Texture* bloc_v = SDL_CreateTextureFromSurface(renderer, bloc1);
    SDL_Texture* bloc_T = SDL_CreateTextureFromSurface(renderer, bloc2);

    int map[N][N]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0
                  0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0
                  0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}


    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                        quit = 1;
                        break;
            }
        }




    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    dessin_map(map,Button,renderer,bloc_h,bloc_T,bloc_v);
    SDL_RenderPresent(renderer);

    }

    SDL_DestroyTexture(bloc_v);
    SDL_DestroyTexture(bloc_T);
    SDL_DestroyTexture(bloc_h);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}