#ifndef TEXT_ECRIRE_H
#define TEXT_ECRIRE_H

#include "../common/common.h"



/**
 * @brief Fonction pour dessiner du texte encadré dans un rectangle avec des sauts de ligne
 * 
 * @param renderer Le renderer SDL à utiliser pour dessiner
 * @param font La police de caractères à utiliser pour le texte
 * @param text Le texte à dessiner
 * @param x La position en X du coin supérieur gauche du rectangle
 * @param y La position en Y du coin supérieur gauche du rectangle 
 * @param maxWidth La largeur maximale du rectangle
 * @param maxHeight La hauteur maximale du rectangle
 * @param textColor La couleur du texte
 * @param bgColor La couleur de fond du rectangle
 * @param boundingRect Le rectangle englobant dans lequel le texte est dessiné
 */
void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int maxWidth, int maxHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

/**
 * @brief Fonction pour dessiner du texte encadré dans un rectangle avec des sauts de ligne et des statistiques supplémentaires
 * 
 * @param renderer Le renderer SDL à utiliser pour dessiner
 * @param font La police de caractères à utiliser pour le texte
 * @param name Le nom à afficher
 * @param classe La classe à afficher
 * @param pv Les points de vie à afficher
 * @param force La force à afficher
 * @param x La position en X du coin supérieur gauche du rectangle
 * @param y La position en Y du coin supérieur gauche du rectangle
 * @param maxWidth La largeur maximale du rectangle
 * @param maxHeight La hauteur maximale du rectangle
 * @param textColor La couleur du texte
 * @param bgColor La couleur de fond du rectangle
 * @param boundingRect Le rectangle englobant dans lequel le texte est dessiné
 */
void drawTextWithStats(SDL_Renderer *renderer, TTF_Font *font, char *name, char *classe, int pv, int force, int x, int y, int maxWidth, int maxHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);

#endif /* TEXT_ECRIRE_H */
