#ifndef BOUTON_H
#define BOUTON_H

#include "../common/common.h"




// Initialiser un bouton avec les coordonnées et dimensions spécifiées
Button initButton(int x, int y, int width, int height);

// Obtenir le rectangle d'un bouton à partir de ses coordonnées
SDL_Rect getButtonRect(int bouttonx, int bouttony);

// Coller une image sur un bouton
void setButtonImage(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect);

#endif /* BOUTON_H */
