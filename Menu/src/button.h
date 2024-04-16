#ifndef BUTTON_H
#define BUTTON_H

#include "commonSDL.h"



// Structure pour représenter un bouton

// Fonction pour initialiser un bouton
Button create_Button(int x, int y, SDL_Texture *texture);

// Fonction pour afficher un bouton
void render_Button(Button button, SDL_Renderer *renderer);

#endif /* BUTTON_H */
