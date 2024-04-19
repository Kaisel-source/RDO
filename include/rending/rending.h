/**
 * @file rending.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-04-14
*/

#ifndef RENDING_H
#define RENDING_H
#include "../common/board.h"

/**
 * @brief Load the area
 * 
 * @param render Renderer
 * @return SDL_Texture** 
 
*/
SDL_Texture** load_area(SDL_Renderer **render) ;

/**
 * @brief make the rendering of the game
 * 
 * @param render Renderer* 
 * @param g Game structure
 * @param font Font of the text
 * @param textColor Color of the text
 * @param bgColor Color of the background
 * @param boundingRect Rectangle of the text
 * @param i Index of the area
 * 
 */
int rending(SDL_Renderer **render,game_s *g,TTF_Font *font, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect,int i,int suite);
 

#endif