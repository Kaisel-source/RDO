#include "../../include/freeing/freeing.h"



int free_area(SDL_Texture ***area){
    for(int i=0;i<NB_AREA;i++){
        SDL_DestroyTexture((*area)[i]);
    }
    free(*area);
    return 0;
}

int free_map(map_t **map){
    for(int i=0;i<NB_MAP_Y;i++){
        for(int j=0;j<NB_MAP_X;j++){
                free((*map)->map[i][j]);
                free((*map)->path[i][j]);
            }
            free((*map)->map[i]);
        }
        
    
    free((*map)->map);
    free(*map);
    return 0;

}