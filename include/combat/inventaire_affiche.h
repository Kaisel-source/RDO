#ifndef INVENTORY_D_H
#define INVENTORY_D_H

#include "../common/common.h"


#define ITEM_COUNT 3


// Structure pour représenter un article
/**
 * @brief affiche la description + le nom d un item dans une case defini a un lieu sur le rendue
 * 
 * @param renderer rendue
 * @param font police
 * @param name nom item
 * @param description description d item
 * @param x placement du rectangle 
 * @param y placement du rectangle 
 * @param maxWidth taille du rectangle 
 * @param maxHeight taille du rectangle 
 * @param textColor couleur du text
 * @param bgColor couleur du fond de  text 
 * @param boundingRect rectangle
 */
void draw_Inventory(SDL_Renderer *renderer, TTF_Font *font, char *name, char *description, int x, int y, int maxWidth, int maxHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

/**
 * @brief montre un text a ecrire centrer dans un bouton a des coordonner specifier 
 * 
 * @param renderer rendue
 * @param font police
 * @param text text ecrire 
 * @param x placement du rectangle 
 * @param y placement du rectangle 
 * @param width taille du rectangle 
 * @param height taille du rectangle 
 * @param bgColor couleur du fond de text 
 * @param textColor 
 */
void draw_Button(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int width, int height, SDL_Color bgColor, SDL_Color textColor);

/**
 * @brief montre l item courent de l inventaire 
 * 
 * @param inventory l inventaire
 * @param font police
 * @param renderer rendue 
 * @param textColor couleur 
 * @param bgColor couleur 
 * @param boundingRect renctangle ou afficher 
 * @param suite passe a l item suivant 
 */
void show_Inventory(item_list *inventory, TTF_Font *font, SDL_Renderer *renderer, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect,int suite);

/**
 * @brief cache l inventaire 
 * 
 * @param boundingRect la ou afficher l inventaire 
 * @param renderer rendue 
 * @param inventoryVisible si activer la fonction 
 */
void toggle_Inventory_Visibility(SDL_Rect *boundingRect, SDL_Renderer *renderer, int *inventoryVisible);

#endif /* INVENTORY_D_H */
