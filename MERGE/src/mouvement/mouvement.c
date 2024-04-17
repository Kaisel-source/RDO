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
    case TILES:
        return 1;
        break;
    default:
        return 0;
        break;
    }
    
}
int interact(game_s *game, int x, int y, SDL_Renderer *renderer, SDL_Window *window) {
    int num_map_x = game->map->x;
    int num_map_y = game->map->y;
    
    entite_t plateau_de_combat[GRID_ROWS][GRID_COLUMNS]; // Déclaration déplacée ici
    
    switch (game->map->map[num_map_y][num_map_x][y][x]) {
        case DOOR_O:
            game->map->map[num_map_y][num_map_x][y][x] = DOOR_C;
            break;
        case DOOR_C:
            game->map->map[num_map_y][num_map_x][y][x] = DOOR_O;
            break;
        case MONSTER:
            init_plateau(plateau_de_combat);
            // Création de perso1 prenom/classe/pv/pv_max/force/equipe/mouv/iniative/range
            entite_t perso1 = create_entity("Bob", "Guerrier", 100, 100, 20, 1, 3, 15, 5);
            entite_t perso2 = create_entity("Goblin", "Brigand", 100, 100, 100, 2, 2, 10, 5);

            SDL_Surface* persoSurface1 = IMG_Load("img/ennemi.png");
            if (persoSurface1 == NULL) {
                printf("Erreur de l'image : %s\n", IMG_GetError());
                return 1;
            }
            SDL_Surface* persoSurface2 = IMG_Load("img/allie.png");
            if (persoSurface2 == NULL) {
                printf("Erreur de l'image : %s\n", IMG_GetError());
                return 1;
            }
            SDL_Surface* perdue = IMG_Load("img/game_over.jpeg");
            if (perdue == NULL) {
                printf("Erreur de l'image : %s\n", IMG_GetError());
                return 1;
            }

            SDL_Texture * perdueTexture = SDL_CreateTextureFromSurface(renderer, perdue);
            perso1.img = SDL_CreateTextureFromSurface(renderer, persoSurface1);
            perso2.img = SDL_CreateTextureFromSurface(renderer, persoSurface2);

            SDL_FreeSurface(persoSurface2);
            SDL_FreeSurface(persoSurface1);
            SDL_FreeSurface(perdue);

            plateau_de_combat[0][0] = perso1;
            plateau_de_combat[5][5] = perso2;

            int gagnant = combat(plateau_de_combat, window, renderer);
            printf("%d", gagnant);
            if (gagnant == -1) {
                SDL_RenderCopy(renderer, perdueTexture, NULL, NULL); // Écran game over
            }

            SDL_Delay(1000);

            SDL_DestroyTexture(perso1.img);
            SDL_DestroyTexture(perso2.img);
            break;
        case SORTIE:
            printf("X : %d\n", x);
            export_board(&(game->map->map[num_map_y][num_map_x]), game->map->path[num_map_y][num_map_x]);
            if (y == 0) {
                if (num_map_y - 1 >= 0) {
                    game->map->y = num_map_y - 1;
                    game->map->x = num_map_x;
                    game->main_perso->y = BOARD_SIZE_Y - 1;
                }
            }
            else if (y == BOARD_SIZE_Y - 1) {
                if (num_map_y + 1 < NB_MAP_Y) {
                    game->map->y = num_map_y + 1;
                    game->map->x = num_map_x;
                    game->main_perso->y = 0;
                }
            }
            else if (x == 0) {
                printf("X : %d\n", x);
                if (num_map_x - 1 >= 0) {
                    game->map->y = num_map_y;
                    game->map->x = num_map_x - 1;
                    game->main_perso->x = BOARD_SIZE_X - 1;
                }
            }
            else if (x == BOARD_SIZE_X - 1) {
                if (num_map_x + 1 < NB_MAP_X) {
                    game->map->y = num_map_y;
                    game->map->x = num_map_x + 1;
                    game->main_perso->x = 0;
                }
            }
            
            export_board(&(game->map->map[num_map_y][num_map_x]), game->map->path[num_map_y][num_map_x]);
            break;
        default:
            printf("Interact with npc\n");
            if (game->map->map[num_map_y][num_map_x][y][x] > 0 && game->map->map[num_map_y][num_map_x][y][x] <= game->nb_pers_saved) {
                printf("Interact with npc\n");
                npc_interact(game->main_perso, game->npc[game->map->map[num_map_y][num_map_x][y][x] - 1]);
            }
            break;
    }
    return 0;
}

    
