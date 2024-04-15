#include "../../include/mouvement/mouvement.h"

int collision(int (*board)[24][24],int x,int y){
    printf("%d %d\n",x,y);
    switch ((*board)[y][x])
    {
    case 0:
        return 1;
        break;
    case DOOR_O:
        return 1;
        break;
    case WATER:
        return 1;
        break;
    default:
        return 0;
        break;
    }
    
}

int interact(game_s *game,int x,int y){
    int num_map_x = game->map->x;
    int num_map_y = game->map->y;
    
    switch (game->map->map[num_map_y][num_map_x][y][x]){
        case DOOR_O:
            game->map->map[num_map_y][num_map_x][y][x] = DOOR_C;
            break;
        case DOOR_C:
            game->map->map[num_map_y][num_map_x][y][x] = DOOR_O;
            break;
        case SORTIE:
            printf("X : %d\n",x);
            export_board(&(game->map->map[num_map_y][num_map_x]), game->map->path[num_map_y][num_map_x]);
            if(y==0){
                if(num_map_y-1>=0){
                    game->map->y = num_map_y-1;
                    game->map->x = num_map_x;
                    game->main_perso->y = BOARD_SIZE_Y-1;
                }
            }
            else if(y==BOARD_SIZE_Y-1){
                if(num_map_y+1<NB_MAP_Y){
                    game->map->y = num_map_y+1;
                    game->map->x = num_map_x;
                    game->main_perso->y = 0;
                }
            }
            else if(x==0){
                printf("X : %d\n",x);
                if(num_map_x-1>=0){
                    game->map->y = num_map_y;
                    game->map->x = num_map_x-1;
                    game->main_perso->x = BOARD_SIZE_X-1;
                }
            }
            else if(x==BOARD_SIZE_X-1){
                if(num_map_x+1<NB_MAP_X){
                    game->map->y = num_map_y;
                    game->map->x = num_map_x+1;
                    game->main_perso->x = 0;
                }
            }
            
            export_board(&(game->map->map[num_map_y][num_map_x]), game->map->path[num_map_y][num_map_x]);


            break;
        default:
            printf("Interact with npc\n");
            if(game->map->map[num_map_y][num_map_x][y][x] > 0 && game->map->map[num_map_y][num_map_x][y][x] <= game->nb_pers_saved){
                printf("Interact with npc\n");
                npc_interact(game->main_perso,game->npc[game->map->map[num_map_y][num_map_x][y][x]-1]);
            }
                
            break;
    }
    return 0;
}
    
