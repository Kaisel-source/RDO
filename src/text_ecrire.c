#include "text_ecrire.h"


// La fonction qui dessine du texte encadré dans un rectangle avec des sauts de ligne
void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int maxWidth, int maxHeight,SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect) {
    // Création de la surface de texte à partir de la police et du texte fournis
    SDL_Surface *textSurface = TTF_RenderText_Blended_Wrapped(font, text, textColor, maxWidth);
    if (textSurface == NULL) {
        printf("Erreur lors du rendu du texte : %s\n", TTF_GetError());
        return;
    }

    // Création de la texture à partir de la surface de texte
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Erreur lors de la création de la texture du texte : %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return; 
    }


    // Mise à jour de la hauteur du rectangle englobant
    boundingRect->x = x;
    boundingRect->y = y;
    boundingRect->w = maxWidth;
    boundingRect->h = maxHeight;

    // Dessin du rectangle de fond
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, boundingRect);

    // Dessin du texte
    SDL_Rect renderRect = { x, y, 0, 0 };
    SDL_QueryTexture(textTexture, NULL, NULL, &renderRect.w, &renderRect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &renderRect);

    // Libération de la surface et de la texture
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void drawTextWithStats(SDL_Renderer *renderer, TTF_Font *font,char *name,char *classe, int pv, int force, int x, int y, int maxWidth, int maxHeight,SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect) {
    char statsText[100]; // Pour stocker le texte des statistiques

    // Création du texte des statistiques
    snprintf(statsText, sizeof(statsText), "%s\nClasse: %s \nPV: %d\nForce: %d", name,classe, pv, force);

    // Création de la surface de texte à partir du texte des statistiques
    SDL_Surface *textSurface = TTF_RenderText_Blended_Wrapped(font, statsText, textColor, maxWidth);
    if (textSurface == NULL) {
        printf("Erreur lors du rendu du texte : %s\n", TTF_GetError());
        return;
    }

    // Création de la texture à partir de la surface de texte
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Erreur lors de la création de la texture du texte : %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }


    // Mise à jour de la hauteur du rectangle englobant
    boundingRect->x = x;
    boundingRect->y = y;
    boundingRect->w = maxWidth;
    boundingRect->h = maxHeight;

    // Dessin du rectangle de fond
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, boundingRect);

    // Dessin du texte
    SDL_Rect renderRect = { x, y, 0, 0 };
    SDL_QueryTexture(textTexture, NULL, NULL, &renderRect.w, &renderRect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &renderRect);

    // Libération de la surface et de la texture
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
