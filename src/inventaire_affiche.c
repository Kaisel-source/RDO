#include "inventaire_affiche.h" 





// Fonction pour créer un item
Item createItem(char *name,char *description) {
    Item item;
    item.name = name;
    item.description = description;
    return item;
}

// Fonction pour afficher l'inventaire
void showInventory(SDL_Renderer *renderer, TTF_Font *font, Item items[], int itemCount) {
    SDL_Color textColor = {255, 255, 255}; // Couleur du texte
    SDL_Surface *textSurface;
    SDL_Texture *textTexture;
    SDL_Rect dstRect;
    int i, yOffset = 50; // Offset pour positionner les articles

    // Effacer le rendu précédent
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Afficher chaque article
    for (i = 0; i < itemCount; ++i) {
        // Créer la surface de texte
        textSurface = TTF_RenderText_Solid(font, items[i].name, textColor);
        // Créer la texture de texte
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        // Positionner et afficher le texte
        dstRect.x = 50;
        dstRect.y = yOffset;
        SDL_QueryTexture(textTexture, NULL, NULL, &dstRect.w, &dstRect.h);
        SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
        // Mettre à jour l'offset pour le prochain article
        yOffset += 30;

        // Description
        textSurface = TTF_RenderText_Solid(font, items[i].description, textColor);
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        dstRect.x = 150;
        SDL_QueryTexture(textTexture, NULL, NULL, &dstRect.w, &dstRect.h);
        SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
        yOffset += 30;
    }

    // Rafraîchir le rendu
    SDL_RenderPresent(renderer);
}

