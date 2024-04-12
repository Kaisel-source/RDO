#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 75
#define BUTTON_MARGIN 20

// Structure pour représenter un bouton
typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
} Button;


// Fonction pour initialiser un bouton
Button create_Button(int x, int y, SDL_Texture *texture);


// Fonction pour afficher un bouton
void render_Button(Button button, SDL_Renderer *renderer);


int game_over();