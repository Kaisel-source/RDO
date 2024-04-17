/**
 * @file button.h
 * @author Nathan Duval
 * @brief 
 * @version 0.1
 * @date 2024-04-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef BUTTON_H
#define BUTTON_H

#include "commonSDL.h"



/**
 * @brief Create a Button object
 * 
 * @param x 
 * @param y 
 * @param texture 
 * @return Button 
 */
// Fonction pour initialiser un bouton
Button create_Button(int x, int y, SDL_Texture *texture);

/**
 * @brief 
 * 
 * @param button 
 * @param renderer 
 */
// Fonction pour afficher un bouton
void render_Button(Button button, SDL_Renderer *renderer);

#endif /* BUTTON_H */
