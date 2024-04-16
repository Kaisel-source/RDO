#ifndef COMMONSDL_H
#define COMMONSDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>



#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 75
#define BUTTON_MARGIN 20


typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
} Button;



#include "option.h"
#include "button.h"
#include "menu.h"



#endif /* COMMONSDL_H */