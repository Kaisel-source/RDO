/**
 * @file mouvement.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-04-14
*/

#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include "../common/board.h"

/**
 * @brief Check the collision
 * 
 * @param board Board of the game
 * @param x X position
 * @param y Y position
*/
int collision(int (*board)[24][24],int x,int y);

/**
 * @brief Interaction of the personnage
 * 
 * @param game Game 
 * @param x X position
 * @param y Y position
 * @param renderer Renderer
 * @param window Window
*/
int interact(game_s *game,int x,int y,SDL_Renderer *renderer,SDL_Window *window);

#endif