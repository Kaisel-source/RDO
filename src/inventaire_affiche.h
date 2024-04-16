#ifndef INVENTORY_H
#define INVENTORY_H

#include "commun.h"


#define ITEM_COUNT 3


// Structure pour représenter un article
typedef struct {
    char *name;
    char *description;
} Item;

void drawInventory(SDL_Renderer *renderer, TTF_Font *font, char *name, char *description, int x, int y, int maxWidth, int maxHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

void drawButton(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int width, int height, SDL_Color bgColor, SDL_Color textColor);

void showInventory(int nbItems, Item *inventory, TTF_Font *font, SDL_Renderer *renderer, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

void toggleInventoryVisibility(SDL_Rect *boundingRect, SDL_Renderer *renderer, int *inventoryVisible);

#endif /* INVENTORY_H */
