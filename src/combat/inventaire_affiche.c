#include "../../include/common/common.h"

void draw_Inventory(SDL_Renderer *renderer, TTF_Font *font, char *name, char *description, int x, int y, int maxWidth, int maxHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect) {
    char statsText[100]; // Pour stocker le texte des statistiques

    // Création du texte des statistiques
    snprintf(statsText, sizeof(statsText), "Nom : %s \n | Description : %s", name, description);

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

void draw_Button(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int width, int height, SDL_Color bgColor, SDL_Color textColor) {
    // Dessiner le rectangle du bouton
    SDL_Rect buttonRect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &buttonRect);

    // Afficher le texte du bouton
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = { x + (width - textWidth) / 2, y + (height - textHeight) / 2, textWidth, textHeight };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Libérer les ressources
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void show_Inventory(item_list *inventory, TTF_Font *font, SDL_Renderer *renderer, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect,int suite) {
    type_it type;
    draw_Button(renderer,font," -> ",400+300, 100 , 50, 100,bgColor,textColor);
    for (int i = 0; i < 1; i++) {
        type = inventory->current->item_inv->type;
        if(type == RESSOURCE){
            draw_Inventory(renderer, font, inventory->current->item_inv->item_u->ress->name, inventory->current->item_inv->item_u->ress->desc, 100, 100 + i * 100, 300, 100, textColor, bgColor, boundingRect);
        }
        if(type == EQPMT){
            draw_Inventory(renderer, font, inventory->current->item_inv->item_u->eqpmt->name, inventory->current->item_inv->item_u->eqpmt->desc, 100, 100 + i * 100, 300, 100, textColor, bgColor, boundingRect);
        }
        if(type == CONSUM){
            draw_Inventory(renderer, font, inventory->current->item_inv->item_u->conso->name, inventory->current->item_inv->item_u->conso->desc, 100, 100 + i * 100, 300, 100, textColor, bgColor, boundingRect);
        }
        
        draw_Button(renderer,font,"miam",100+300, 100 + i * 100, 300, 100,bgColor,textColor);
    }
}

void toggle_Inventory_Visibility(SDL_Rect *boundingRect, SDL_Renderer *renderer, int *inventoryVisible) {
    *inventoryVisible = !(*inventoryVisible);

    // Effacement de l'inventaire si nécessaire
    if (!(*inventoryVisible)) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, boundingRect);
        SDL_RenderPresent(renderer);
    }
}


