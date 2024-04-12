#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"




/**
 * @brief position + image d un espace defeni
 * 
 */
typedef struct {
    SDL_Rect rect;       // Rectangle définissant la position et la taille du bouton
    SDL_Texture* texture; // Texture du bouton (à générer avec SDL_CreateTextureFromSurface())
} Button;


Button initButton(int x, int y, int width, int height);


SDL_Rect getButtonRect(int bouttonx, int bouttony);


void setButtonImage(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect);