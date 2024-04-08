#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// La fonction qui dessine du texte encadré dans un rectangle avec des sauts de ligne
void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int maxWidth, int maxHeight, int lineHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect) {
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

    // Obtention des dimensions de la surface de texte
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

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

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() < 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("Texte encadré", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargement de la police de caractères
    TTF_Font *font = TTF_OpenFont("../img/police.ttf", 15);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police de caractères : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Couleurs
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Color bgColor = { 30, 30, 30, 255 };

    // Texte à dessiner
    const char *text = "Ceci est un exemple de texte \n qui sera encadre.";

    // Coordonnées et hauteur de saut de ligne
    int x = 100;
    int y = 100;
    int lineHeight = 30;

    // Rectangle englobant
    SDL_Rect boundingRect;

    // Dessin du texte encadré
    drawText(renderer, font, text, x, y, 400, 400, lineHeight, textColor, bgColor, &boundingRect);

    // Rafraîchissement de l'affichage
    SDL_RenderPresent(renderer);

    // Attente d'un événement de fermeture de fenêtre
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // Libération des ressources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
