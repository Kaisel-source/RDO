#ifndef RENDING_H
#define RENDING_H
#include "../common/board.h"

SDL_Texture** load_area(SDL_Renderer **render) ;
int rending(SDL_Renderer **render,game_s *g);

#endif