#ifndef RENDING_H
#define RENDING_H
#include "../common/common.h"

SDL_Texture** load_area(SDL_Renderer **render) ;
int rending(SDL_Renderer **render,personnage_t *perso,int map[24][24],SDL_Texture **area,SDL_Texture *TextureOut);

#endif