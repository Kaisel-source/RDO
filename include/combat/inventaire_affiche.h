/**
 * @file inventaire_affiche.h
 * @author Mael Gaumont
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/
#ifndef INVENTORY_D_H
#define INVENTORY_D_H

#include "../common/common.h"


#define ITEM_COUNT 3


// Structure pour représenter un article

void draw_Inventory(SDL_Renderer *renderer, TTF_Font *font, char *name, char *description, int x, int y, int maxWidth, int maxHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

void draw_Button(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int width, int height, SDL_Color bgColor, SDL_Color textColor);

void show_Inventory(item_list *inventory, TTF_Font *font, SDL_Renderer *renderer, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

void toggle_Inventory_Visibility(SDL_Rect *boundingRect, SDL_Renderer *renderer, int *inventoryVisible);

#endif /* INVENTORY_D_H */
