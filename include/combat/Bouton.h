#ifndef BOUTON_H
#define BOUTON_H

#include "../common/common.h"



/**
 * @brief // Initialiser un bouton avec les coordonnées et dimensions spécifiées
 * 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 * @return Button 
 */
Button init_Button(int x, int y, int width, int height);

/**
 * @brief // Obtenir le rectangle d'un bouton à partir de ses coordonnées
 * 
 * @param bouttonx 
 * @param bouttony 
 * @return SDL_Rect 
 */
SDL_Rect get_Button_Rect(int bouttonx, int bouttony);

/**
 * @brief // Coller une image sur un bouton
 * 
 * @param renderer 
 * @param imageTexture 
 * @param buttonRect 
 */
void set_Button_Image(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect);

#endif /* BOUTON_H */
