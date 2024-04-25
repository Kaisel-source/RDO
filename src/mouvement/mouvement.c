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
int interact(game_s *game, int x, int y, SDL_Renderer *renderer, SDL_Window *window,char ** parler) {
    int num_map_x = game->map->x;
    int num_map_y = game->map->y;
    int suite=0;

    
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
            int pv = game->main_perso->hp;
            int pv_max = game->main_perso->hp_max;
            int force = total_strength(*(game->main_perso));
            int initiative = total_agility(*(game->main_perso));
            int mov=total_endurance(*(game->main_perso));
            
            entite_t perso1 = create_entity("Goblin", "Brigand", 10, 10, 1, 1, 2, 100, 5);
            entite_t perso2 = create_entity(game->main_perso->name, "Guerrier", pv, pv_max, force, 2, mov, initiative, 5);

            SDL_Surface* persoSurface1 = IMG_Load("data/image/combat/GOBELIN.webp");
            if (persoSurface1 == NULL) {
                printf("Erreur de l'image : %s\n", IMG_GetError());
                return 1;
            }
            SDL_Surface* persoSurface2 = IMG_Load("data/image/combat/PERSO_COMBAT.webp");
            if (persoSurface2 == NULL) {
                printf("Erreur de l'image : %s\n", IMG_GetError());
                return 1;
            }
            SDL_Surface* perdue = IMG_Load("data/image/combat/game_over.jpeg");
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
            if(gagnant ==1){
                take_item(game->main_perso, game->item->head);
                game->map->map[num_map_y][num_map_x][y][x] = 0;
                
            }
            if (gagnant == -1) {
                SDL_RenderCopy(renderer, perdueTexture, NULL, NULL); // Écran game over
                import(&(game->main_perso));
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
            
            if (game->map->map[num_map_y][num_map_x][y][x] > 0 && game->map->map[num_map_y][num_map_x][y][x] <= game->nb_pers_saved) {
                suite=1;
                *parler=malloc(strlen(game->npc[game->map->map[num_map_y][num_map_x][y][x] - 1]->dialog)+1 * sizeof(char));
                strcpy(*parler,game->npc[game->map->map[num_map_y][num_map_x][y][x] - 1]->dialog);
                npc_interact(game->main_perso, game->npc[game->map->map[num_map_y][num_map_x][y][x] - 1]);
                if(game->npc[game->map->map[num_map_y][num_map_x][y][x] - 1]->nb_quest>0){
                    
                    accept_quest(game->main_perso, game->quest[0]);
                }
            }
            break;
    }
    return suite;
}

    
