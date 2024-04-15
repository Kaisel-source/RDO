#ifndef INVENTORY_H
#define INVENTORY_H

#include "commun.h"


#define ITEM_COUNT 3


// Structure pour représenter un article
typedef struct {
    char *name;
    char *description;
} Item;

// Fonction pour créer un article
Item createItem(char *name, char *description);

// Fonction pour afficher l'inventaire
void showInventory(SDL_Renderer *renderer, TTF_Font *font, Item items[], int itemCount);

#endif /* INVENTORY_H */
