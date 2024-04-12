#include "../../include/rending/rending.h"

SDL_Texture** load_area(SDL_Renderer **render) {
    SDL_Surface **Surface = malloc(sizeof(SDL_Surface *) * NB_AREA);
    if (Surface == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour les surfaces.\n");
        return NULL;
    }

    char path[40];
    for (int i = 0; i < NB_AREA; i++) {
        sprintf(path, "image/area/%d.png", i); // Utilisation de sprintf pour concaténer les chaînes de caractères
        Surface[i] = IMG_Load(path);
        if (Surface[i] == NULL) {
            printf("Erreur lors du chargement de l'image : %s\n", SDL_GetError());
            for (int j = 0; j < i; j++) {
                SDL_FreeSurface(Surface[j]); // Libérer les surfaces déjà chargées
            }
            free(Surface); // Libérer la mémoire allouée pour les surfaces
            return NULL;
        }
    }

    SDL_Texture **area = malloc(sizeof(SDL_Texture *) * NB_AREA);
    if (area == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour les textures.\n");
        for (int i = 0; i < NB_AREA; i++) {
            SDL_FreeSurface(Surface[i]); // Libérer les surfaces déjà chargées
        }
        free(Surface); // Libérer la mémoire allouée pour les surfaces
        return NULL;
    }

    for (int i = 0; i < NB_AREA; i++) {
        area[i] = SDL_CreateTextureFromSurface(*render, Surface[i]);
        if (area[i] == NULL) {
            printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
            for (int j = 0; j < i; j++) {
                SDL_DestroyTexture(area[j]); // Libérer les textures déjà créées
            }
            free(area); // Libérer la mémoire allouée pour les textures
            for (int j = 0; j < NB_AREA; j++) {
                SDL_FreeSurface(Surface[j]); // Libérer les surfaces déjà chargées
            }
            free(Surface); // Libérer la mémoire allouée pour les surfaces
            return NULL;
        }
    }

    for (int i = 0; i < 4; i++) {
        SDL_FreeSurface(Surface[i]); // Libérer les surfaces maintenant que les textures ont été créées
    }
    free(Surface); // Libérer la mémoire allouée pour les surfaces

    return area;
}

int rending(SDL_Renderer **render,personnage_t *perso,int map[24][24],SDL_Texture **area,SDL_Texture *TextureOut){
    SDL_RenderClear(*render); // Effacer le rendu précédent
    // Dessiner le plateau
    for(int i=0;i<BOARD_SIZE_Y;i++){
            for(int j=0;j<BOARD_SIZE_X;j++){
                SDL_Rect rect = {j * CELL_WIDTH, i * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT};
                SDL_RenderCopy(*render, area[0], NULL, &rect);
                if(abs(map[i][j]) <= NB_AREA)
                    SDL_RenderCopy(*render, area[abs(map[i][j])], NULL, &rect);
                else if(map[i][j] == SORTIE)
                    SDL_RenderCopy(*render, TextureOut, NULL, &rect);

            }
        }
    // Dessiner le personnage
    perso->position->y = (perso->y * (WINDOW_HEIGHT / BOARD_SIZE_Y)) % WINDOW_HEIGHT;
    perso->position->x = (perso->x * (WINDOW_WIDTH / BOARD_SIZE_X)) % WINDOW_WIDTH;
    SDL_RenderCopy(*render, perso->Texture, perso->sprite_move[perso->direction]->texture[perso->sprite_move[perso->direction]->num_ref], perso->position);
    SDL_RenderPresent(*render);
    return 0;
}