/**
 * @file Bouton.h
 * @author Mael Gaumont
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/

#ifndef BOUTON_H
#define BOUTON_H

#include "../common/common.h"




// Initialiser un bouton avec les coordonnées et dimensions spécifiées
Button init_Button(int x, int y, int width, int height);

// Obtenir le rectangle d'un bouton à partir de ses coordonnées
SDL_Rect get_Button_Rect(int bouttonx, int bouttony);

// Coller une image sur un bouton
void set_Button_Image(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect);

#endif /* BOUTON_H */
