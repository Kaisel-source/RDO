/**
 * @file option.h
 * @author Nathan Duval
 * @brief 
 * @version 0.1
 * @date 2024-04-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef OPTION_H
#define OPTION_H

#include "../common/board.h"
#include "../common/struct.h"
#include "../common/common.h"

/**
 * @brief 
 * 
 * @param renderer 
 * @param saveButton 
 * @param loadButton 
 * @param deleteButton 
 * @param quitButton2 
 * @param settingsPage  
 */
void option(SDL_Renderer *renderer, Button saveButton, Button loadButton, Button deleteButton, Button quitButton2, int *settingsPage);

#endif /* OPTION_H */
