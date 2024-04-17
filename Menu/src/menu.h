/**
 * @file menu.h
 * @author Nathan Duval
 * @brief 
 * @version 0.1
 * @date 2024-04-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef MENU_H
#define MENU_H

#include "commonSDL.h"


/**
 * @brief 
 * 
 * @param renderer 
 * @param playButton 
 * @param settingsButton 
 * @param quitButton 
 * @param running 
 * @param settingsPage 
 */
void menu(SDL_Renderer *renderer, Button playButton, Button settingsButton, Button quitButton, int *running, int *settingsPage);

#endif /* MENU_H */
