#ifndef INVENTORY_D_H
#define INVENTORY_D_H

#include "../common/common.h"


#define ITEM_COUNT 3


// Structure pour représenter un article

void drawInventory(SDL_Renderer *renderer, TTF_Font *font, char *name, char *description, int x, int y, int maxWidth, int maxHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

void drawButton(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int width, int height, SDL_Color bgColor, SDL_Color textColor);

void showInventory(item_list *inventory, TTF_Font *font, SDL_Renderer *renderer, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

void toggleInventoryVisibility(SDL_Rect *boundingRect, SDL_Renderer *renderer, int *inventoryVisible);

#endif /* INVENTORY_D_H */
