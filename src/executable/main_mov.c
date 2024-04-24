#include "../../include/common/common.h"





int main() {  
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("SDL Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return -1;
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        return -1;
    }

    // Initialisation de SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        return -1;
    }

    
    int map_build = 0;


    /*PERSONNAGE*/
    perso *perso=malloc(sizeof(perso));
    init_perso(perso, "tata", 1,1,1,1,1,11,23, UP, &renderer);

    import(&perso);
    printf("%s\n",perso->name);
    printf("%d %d\n",perso->x,perso->y);


    
    /*MAP*/
    SDL_Texture **area = load_area(&renderer);
    map_t map;
    map.x = perso->map_x;
    map.y = perso->map_y;
    
    
    for(int y=0;y<NB_MAP_Y;y++){
        for(int x=0;x<NB_MAP_X;x++){
            map.path[y][x] = malloc(sizeof(char)*30);
            sprintf(map.path[y][x], "data/map/board%d-%d.txt", y, x);
            import_board(&map.map[y][x],map.path[y][x]);
        }
    }
    
    
    SDL_Surface *SurfaceOut = IMG_Load("data/image/area/OUT.png");
    SDL_Texture *TextureOut = SDL_CreateTextureFromSurface(renderer, SurfaceOut);
    SDL_FreeSurface(SurfaceOut);

    SurfaceOut = IMG_Load("data/image/area/MONSTER.png");
    SDL_Texture *TextureMonster = SDL_CreateTextureFromSurface(renderer, SurfaceOut);
    SDL_FreeSurface(SurfaceOut);


    /*GAME*/
    game_s *g = malloc(sizeof(game_s));
    game_init_game(g,&map,TextureOut,TextureMonster,area);
    game_add_main_perso(g,perso);

    /*QUETE*/
    item_t *ress;
    ress = ress_creator(1,"Oreille de Gobelin",10,10,"Une Oreille de gobelin",1);
    game_add_item(g,ress);

    item_t *item = malloc(sizeof(item_t));
    item = eqpmt_creator(1, "Epee", WEAPON, PHYSICAL, 10, 10, 10, 10, 100, 10, 10, 10, 10, "une epee",1);

    quest_t *q;
    q=quest_create("Un pas a la fois","Tuer 10 Monstres",1,NOT_STARTED,100,10,item,1,ress);
    game_add_quest(g,q);
    


    /*NPC*/
    npc_s *npc = npc_creator("toto", "toto", 10, "data/image/perso.png", LEFT, &renderer, 0);
    game_add_npc(g,npc);
    npc = npc_creator("kevin", "Je etre kevin", 10, "data/image/perso.png", LEFT, &renderer, 1,q);
    game_add_npc(g,npc);


    // Chargement de l'icône de la fenêtre
    SDL_Surface* iconSurface = IMG_Load("data/image/menu/Icone.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);


    // Chargement des images des boutons
    SDL_Surface *playSurface = IMG_Load("data/image/menu/bouton_jouer.png");
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Surface *settingsSurface = IMG_Load("data/image/menu/bouton_paramètre.png");
    SDL_Texture *settingsTexture = SDL_CreateTextureFromSurface(renderer, settingsSurface);
    SDL_Surface *quitSurface = IMG_Load("data/image/menu/bouton_quitter.png");
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);

    // Chargement des images des boutons de la fenêtre de paramètres
    SDL_Surface *saveSurface = IMG_Load("data/image/menu/bouton_sauvegarde.png");
    SDL_Texture *saveTexture = SDL_CreateTextureFromSurface(renderer, saveSurface);
    SDL_Surface *loadSurface = IMG_Load("data/image/menu/bouton_charger.png");
    SDL_Texture *loadTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
    SDL_Surface *deleteSurface = IMG_Load("data/image/menu/bouton_reset.png");
    SDL_Texture *deleteTexture = SDL_CreateTextureFromSurface(renderer, deleteSurface);



    // Initialisation des boutons
    Button saveButton = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 200, saveTexture);
    Button loadButton = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 300, loadTexture);
    Button deleteButton = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 400, deleteTexture);
    Button quitButton2 = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 500, quitTexture);
    Button playButton = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, WINDOW_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN_MENU, playTexture);
    Button settingsButton = create_Button(BUTTON_MARGIN_MENU, WINDOW_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN_MENU, settingsTexture);
    Button quitButton = create_Button(WINDOW_WIDTH - BUTTON_WIDTH - BUTTON_MARGIN_MENU, WINDOW_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN_MENU, quitTexture);

    // Libération des surfaces une fois les textures créées
    SDL_FreeSurface(playSurface);
    SDL_FreeSurface(settingsSurface);
    SDL_FreeSurface(quitSurface);
    SDL_FreeSurface(saveSurface);
    SDL_FreeSurface(loadSurface);
    SDL_FreeSurface(deleteSurface);

    
    
    take_item(g->main_perso,item);
    use_eqpmt(g->main_perso,item->item_inv->item_u->eqpmt);
    display_perso(*g->main_perso);
    int running = 1;
    SDL_Event event;
    int settingsPage = 0;
    int play=0;

    
    

    int suite=0;

    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
        }
    TTF_Font *font = TTF_OpenFont("img/police.ttf", 12);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police de caractères : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }



    SDL_Color textColor = { 176, 91, 78, 255 };
    SDL_Color bgColor = { 30, 30, 30, 255 };
    int inventoryVisible = 0;
    SDL_Rect boundingRect;

    while (running) {
        if (play==0 && (!settingsPage)){
            play = menu(renderer, playButton, settingsButton, quitButton, &running, &settingsPage); 
           
        }else if(settingsPage==1){
            option(renderer, saveButton, loadButton, deleteButton, quitButton2, &settingsPage);
        }
        if (play == 1) {
        while (SDL_PollEvent(&event)) {
            
            if (event.type == SDL_QUIT) {
                running = 0;
                export_board(&map.map[map.y][map.x],map.path[map.y][map.x]);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Vérifier si le clic est sur le bouton
                if (mouseX >= 700 && mouseX <= 800 && mouseY >= 100 && mouseY <= 250) {
                    suiv_current(g->main_perso->inventory);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    perso->direction = RIGHT;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_R?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_R){
                    
                        if((perso->x+1>=0 && perso->x+1<BOARD_SIZE_X) && collision(&map.map[map.y][map.x],perso->x+1,perso->y)){
                            perso->x = (perso->x+1)%BOARD_SIZE_X;
                            
                        }
                        else{
                            printf("You can't go there\n");
                        }
                    }
                    perso->state = WALK_R;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    perso->direction = LEFT;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_L?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_L){
                        if((perso->x-1>=0 && perso->x-1<BOARD_SIZE_X) && collision(&map.map[map.y][map.x],perso->x-1,perso->y)){
                            perso->x = (perso->x-1)%BOARD_SIZE_X;
                        }else{
                            printf("You can't go there\n");
                        }
                    }
                    perso->state = WALK_L;
                }
                else if (event.key.keysym.sym == SDLK_UP) {
                    perso->direction = UP;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_U?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_U){
                        if((perso->y-1>=0 && perso->y-1<BOARD_SIZE_Y) && collision(&map.map[map.y][map.x],perso->x,perso->y-1) ){
                            perso->y = (perso->y-1)%BOARD_SIZE_Y;
                        }
                        else{
                            printf("You can't go there\n");
                        }
                        }
                    perso->state = WALK_U;
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    perso->direction = DOWN;
                    perso->sprite_move[perso->direction]->num_ref = perso->state==WALK_D?((perso->sprite_move[perso->direction]->num_ref + 1) % perso->sprite_move[perso->direction]->nb_sprite):0;
                    
                    SDL_Delay(100);
                    if(perso->state == WALK_D){
                        if((perso->y+1>=0 && perso->y+1<BOARD_SIZE_Y) && collision(&map.map[map.y][map.x],perso->x,perso->y+1)){
                            perso->y = (perso->y+1)%BOARD_SIZE_Y;
                        }
                        else{
                            printf("You can't go there\n");
                        }
                    }
                    perso->state = WALK_D;
                }
                
                else if (event.key.keysym.sym == SDLK_e) {
                    printf("Exportation du plateau\n");
                    export_board(&map.map[map.y][map.x],map.path[map.y][map.x]);
                }
                else if (event.key.keysym.sym == SDLK_r) {
                    printf("Reset du plateau\n");
                    import_board(&map.map[map.y][map.x],map.path[map.y][map.x]);
                }
                else if (event.key.keysym.sym == SDLK_a) {
                    printf("Clear du plateau\n");
                    for(int i=0;i<24;i++){
                        for(int j=0;j<24;j++){
                            map.map[map.y][map.x][i][j] = 0;
                        }
                    }
                }
                                
                else if (event.key.keysym.sym == SDLK_i) {
                    // Affichage/masquage de l'inventaire lorsque la touche "i" est enfoncée
                    if(inventoryVisible)
                        inventoryVisible = 0;
                    else
                        inventoryVisible = 1;
       
                }
                else if (event.key.keysym.sym == SDLK_q) {
                    if(perso->direction == RIGHT && perso->x+1<BOARD_SIZE_X)
                        interact(g,(perso->x+1)%BOARD_SIZE_X,perso->y,renderer,window);
                    else if(perso->direction == LEFT && perso->x-1>=0)
                        interact(g,(perso->x-1)%BOARD_SIZE_X,perso->y,renderer,window);
                    else if(perso->direction == UP && perso->y-1>=0)
                        interact(g,perso->x,(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y,renderer,window);
                    else if(perso->direction == DOWN && perso->y+1<BOARD_SIZE_Y)
                        interact(g,perso->x,(perso->y+1 + BOARD_SIZE_Y)%BOARD_SIZE_Y,renderer,window);

                }
                else{
                    if(map_build){
                        if(perso->direction == RIGHT && perso->x+1<BOARD_SIZE_X)
                            pose_block(&map.map[map.y][map.x],event.key.keysym.sym,(perso->x+1)%BOARD_SIZE_X,perso->y);
                        else if(perso->direction == LEFT && perso->x-1>=0)
                            pose_block(&map.map[map.y][map.x],event.key.keysym.sym,(perso->x-1 + BOARD_SIZE_X)%BOARD_SIZE_X,perso->y);
                        else if(perso->direction == UP && perso->y-1>=0)
                            pose_block(&map.map[map.y][map.x],event.key.keysym.sym,perso->x,(perso->y-1 + BOARD_SIZE_Y)%BOARD_SIZE_Y);
                        else if(perso->direction == DOWN && perso->y+1<BOARD_SIZE_Y)
                            pose_block(&map.map[map.y][map.x],event.key.keysym.sym,perso->x,(perso->y+1 + BOARD_SIZE_Y)%BOARD_SIZE_Y);
                    }
                }
            }
    
        
        }

        if(play==1){
            rending(&renderer,g, font, textColor, bgColor, &boundingRect,inventoryVisible,suite);
        } 

        

    } 

    if((play==0)){
            SDL_RenderPresent(renderer);
        }
    }
    // Libération de la mémoire

    // Libération de la mémoire
    SDL_DestroyTexture(playTexture);
    SDL_DestroyTexture(settingsTexture);
    SDL_DestroyTexture(quitTexture);
    
    SDL_DestroyTexture(saveTexture);
    SDL_DestroyTexture(loadTexture);
    SDL_DestroyTexture(deleteTexture);
    
    perso->map_x = map.x;
    perso->map_y = map.y;
    export(perso);
    game_destroy_game(&g);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
   

    return 0;
    
}
