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

int interact(map_t *map,int x,int y,int direction,personnage_t *perso){
    int num_map_x = (map)->x;
    int num_map_y = (map)->y;
    switch ((map)->map[num_map_y][num_map_x][y][x]){
        case DOOR_O:
            (map)->map[num_map_y][num_map_x][y][x] = DOOR_C;
            break;
        case DOOR_C:
            (map)->map[num_map_y][num_map_x][y][x] = DOOR_O;
            break;
        case SORTIE:
            printf("X : %d\n",x);
            export_board(&map->map[map->y][map->x],map->path[map->y][map->x]);
            if(y==0){
                if(num_map_y-1>=0){
                    map->y = num_map_y-1;
                    map->x = num_map_x;
                    perso->y = BOARD_SIZE_Y-1;
                }
            }
            else if(y==BOARD_SIZE_Y-1){
                if(num_map_y+1<NB_MAP_Y){
                    map->y = num_map_y+1;
                    map->x = num_map_x;
                    perso->y = 0;
                }
            }
            else if(x==0){
                printf("X : %d\n",x);
                if(num_map_x-1>=0){
                    map->y = num_map_y;
                    map->x = num_map_x-1;
                    perso->x = BOARD_SIZE_X-1;
                }
            }
            else if(x==BOARD_SIZE_X-1){
                if(num_map_x+1<NB_MAP_X){
                    map->y = num_map_y;
                    map->x = num_map_x+1;
                    perso->x = 0;
                }
            }
            
            import_board(&map->map[map->y][map->x],map->path[map->y][map->x]);

            break;
        default:
            printf("You can't interact with this\n");
            break;
    }
    
}