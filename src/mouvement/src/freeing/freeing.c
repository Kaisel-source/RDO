#include "../../include/freeing/freeing.h"

int free_personnage(personnage_t **perso){
    for(int i=0;i<4;i++){
        for(int j=0;j<9;j++){
            free((*perso)->sprite_move[i]->texture[j]);
        }
        free((*perso)->sprite_move[i]->texture);
        free((*perso)->sprite_move[i]);
    }
    free((*perso)->sprite_move);
    free((*perso)->position);
    free((*perso));
    return 0;
}

int free_area(SDL_Texture ***area){
    for(int i=0;i<NB_AREA;i++){
        SDL_DestroyTexture((*area)[i]);
    }
    free(*area);
    return 0;
}