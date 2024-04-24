#include "../../include/rending/rending.h"

SDL_Texture** load_area(SDL_Renderer **render) {
    SDL_Surface **Surface = malloc(sizeof(SDL_Surface *) * NB_AREA);
    if (Surface == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour les surfaces.\n");
        return NULL;
    }

    char path[40];
    for (int i = 0; i < NB_AREA; i++) {
        sprintf(path, "data/image/area/%d.png", i); // Utilisation de sprintf pour concaténer les chaînes de caractères
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

int rending(SDL_Renderer **render,game_s *g,TTF_Font *font, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect,int cpt,int *settings_enable, Button saveButton, Button loadButton, Button deleteButton, Button quitButton2){
    SDL_RenderClear(*render);  
    // Effacer le rendu précédent
    // Dessiner le plateau
    int map_x = g->map->x;
    int map_y = g->map->y;
    for(int i=0;i<BOARD_SIZE_Y;i++){
            for(int j=0;j<BOARD_SIZE_X;j++){
                SDL_Rect rect = {j * CELL_WIDTH, i * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT};
                SDL_RenderCopy(*render, g->area[0], NULL, &rect);
                if(g->map->map[map_y][map_x][i][j] > 0 && g->map->map[map_y][map_x][i][j] <= g->nb_pers_saved)
                    SDL_RenderCopy(*render, g->npc[g->map->map[map_y][map_x][i][j]-1]->Texture, g->npc[g->map->map[map_y][map_x][i][j]-1]->sprite_move->texture[0], &rect);
                
                else if(g->map->map[map_y][map_x][i][j] == SORTIE)
                    SDL_RenderCopy(*render, g->TextureOut, NULL, &rect);

                else if(g->map->map[map_y][map_x][i][j] == MONSTER)
                    SDL_RenderCopy(*render, g->TextureMonster, NULL, &rect);
                else if(abs(g->map->map[map_y][map_x][i][j]) <= NB_AREA)
                    SDL_RenderCopy(*render, g->area[abs(g->map->map[map_y][map_x][i][j])], NULL, &rect);
               
            
            }
        }
    // Dessiner le personnage
    g->main_perso->position->y = (g->main_perso->y * (WINDOW_HEIGHT / BOARD_SIZE_Y)) % WINDOW_HEIGHT;
    g->main_perso->position->x = (g->main_perso->x * (WINDOW_WIDTH / BOARD_SIZE_X)) % WINDOW_WIDTH;
    if(cpt==1){
        show_Inventory(g->main_perso->inventory, font, *render, textColor, bgColor, boundingRect);
    }
    SDL_RenderCopy(*render, g->main_perso->Texture, g->main_perso->sprite_move[g->main_perso->direction]->texture[g->main_perso->sprite_move[g->main_perso->direction]->num_ref], g->main_perso->position);
    if(*settings_enable == 1){
        option(*render, saveButton, loadButton, deleteButton, quitButton2, settings_enable,g);
        
    }
    SDL_RenderPresent(*render);
    return 0;
}
