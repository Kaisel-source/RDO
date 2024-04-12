#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define ITEM_COUNT 3

typedef struct {
    char *name;
    char *description;
} Item;

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

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Event event;
    int quit = 0;
    int showInventoryFlag = 0; // Indicateur pour montrer ou cacher l'inventaire

    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Création de la fenêtre
    window = SDL_CreateWindow("Inventaire SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de la police
    font = TTF_OpenFont("../img/police.ttf", 24);
    if (font == NULL) {
        printf("Impossible de charger la police : %s\n", TTF_GetError());
        return 1;
    }

    // Liste d'articles
    Item items[ITEM_COUNT] = {
        createItem("Item 1", "Description de l'objet 1"),
        createItem("Item 2", "Description de l'objet 2"),
        createItem("Item 3", "Description de l'objet 3")
    };

    // Boucle principale
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_i) {
                    // Basculer l'affichage de l'inventaire
                    showInventoryFlag = !showInventoryFlag;
                }
            }
        }

        // Afficher ou cacher l'inventaire selon l'indicateur
        if (showInventoryFlag) {
            showInventory(renderer, font, items, ITEM_COUNT);
        }
    }

    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
