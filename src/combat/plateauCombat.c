#include "../../include/common/common.h"


int nombre_Entite(entite_t plateau[N][N]){
    int nb=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(plateau[i][j].pv>0){
                nb++;
            }
        }
    }
    return nb;
}


/**
 * @brief 
 * @param plateau
 */
void init_plateau(entite_t plateau[N][N]){
    for(int i=0;i<GRID_ROWS;i++){
        for(int j=0;j<GRID_COLUMNS;j++){
            initialiser_Entite(&plateau[i][j]);
        }
    }
}


/**
 * @brief Construct a new void object
 * 
 * @param mouseX 
 * @param mouseY 
 */
pos_t plateau_cible(int mouseX,int mouseY,int gridX,int gridY){
    pos_t pos_cible;
    int x=-1,y=-1;
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int column = 0; column < GRID_COLUMNS; column++) {
            int buttonX = gridX + column * (BUTTON_SIZEx + BUTTON_MARGIN);
            int buttonY = gridY + row * (BUTTON_SIZEy + BUTTON_MARGIN);
            if (mouseX >= buttonX && mouseX <= buttonX + BUTTON_SIZEx && mouseY >= buttonY && mouseY <= buttonY + BUTTON_SIZEy) {
                    x=row;
                    y=column;
            }
        }
    }  
    pos_cible.x=x;
    pos_cible.y=y;
    return pos_cible;
}

/**
 * @brief fait le dessin d un echequier
 * 
 * @param plateau_de_combat 
 * @param gridX 
 * @param gridY 
 * @param rien 
 * @param buttonRect 
 * @param renderer 
 */
void dessin_plateau(entite_t plateau_de_combat[N][N],int gridX,int gridY, SDL_Texture* rien,Button buttonRect,SDL_Renderer* renderer){
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int column = 0; column < GRID_COLUMNS; column++) {
            // Calcul de la position du bouton dans la grille
            int buttonX = gridX + column * (BUTTON_SIZEx + BUTTON_MARGIN);
            int buttonY = gridY + row * (BUTTON_SIZEy + BUTTON_MARGIN);
            // Dessiner le rectangle du bouton
            buttonRect.rect.x =  buttonX;   
            buttonRect.rect.y =  buttonY;
            buttonRect.rect.w =  BUTTON_SIZEx;
            buttonRect.rect.h = BUTTON_SIZEy;
            if(plateau_de_combat[row][column].pv>0){
                set_Button_Image(renderer,plateau_de_combat[row][column].img,&buttonRect.rect);
            }else{
                set_Button_Image(renderer,rien,&buttonRect.rect);
            }

        }
    } 
}



int Fin_De_combat(pos_t turn[N*N], int EquipeGagnante, int EquipePerdant, entite_t plateau[N][N]) {
    int cpt1 = 0, cpt2 = 0;
    for (int i = 0; i < (N*N); i++) {
        // Vérifier que les coordonnées x et y sont dans les limites du plateau
        if (turn[i].x >= 0 && turn[i].x < N && turn[i].y >= 0 && turn[i].y < N) {
            if (plateau[turn[i].x][turn[i].y].equipe == EquipeGagnante) {
                cpt1++;
            }
            if (plateau[turn[i].x][turn[i].y].equipe == EquipePerdant) {
                cpt2++;
            }
        }
    }
    if (cpt1 == 0) {
        return 1;
    }else if (cpt2 == 0) {
        return -1;
    }
    return 0;
}


int combat(entite_t plateau_de_combat[N][N],SDL_Window* window,SDL_Renderer* renderer){
    


    //creation du tableau de tour 
    pos_t turn[N*N];
    init_turn_order(turn);

    int FIN=0;
    

    //declare les surfaces de case sous forme de button
    Button buttonRect;
    Button buttonBottom; 
    Button buttonBottom2; 
    Button buttonBottom3; 
    Button buttonBottom4;
    //declare les couleur pour sdl ttf 
    SDL_Color textColor = { 176, 91, 78, 255 };
    SDL_Color bgColor = { 30, 30, 30, 255 };
    SDL_Rect boundingRect;
    SDL_Rect statu;

    // Calcul de la taille de la grille
    int gridWidth = GRID_COLUMNS * (BUTTON_SIZEx + BUTTON_MARGIN) - BUTTON_MARGIN;
    int gridHeight = GRID_ROWS * (BUTTON_SIZEy + BUTTON_MARGIN) - BUTTON_MARGIN;

    // Calcul de la position de la grille
    int gridX = (WINDOW_WIDTH-gridWidth);
    int gridY = (WINDOW_HEIGHT-gridHeight)/2;

    // Calcul de la position du bouton dans le coin bas droit du rectangle inferieur
    int buttonBottomX = WINDOW_WIDTH - BUTTON_SIZEx - BUTTON_MARGIN;
    int buttonBottomY = WINDOW_HEIGHT - BUTTON_SIZEy - BUTTON_MARGIN;

    //charge le fond
    SDL_Surface* backgroundSurface = IMG_Load("data/image/combat/fonddesert.jpg");
    if (backgroundSurface == NULL) {
        printf("Erreur de chargement de l'image de fond : %s\n", IMG_GetError());
        return 1;
    }

    // initialise les image
    SDL_Surface* Casetab = IMG_Load("data/image/combat/New Piskel.png");
    if (Casetab == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface* Fini = IMG_Load("data/image/combat/rectangle.jpg");
    if (Fini == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }


    SDL_Surface* fondinter= IMG_Load("data/image/combat/fondinter.png");
    if (fondinter == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface* att = IMG_Load("data/image/combat/bouton_attaque.png");
    if (att == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface* bouton_avancer = IMG_Load("data/image/combat/bouton_avancer.png");
    if (att == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface* bouton_fin_tour = IMG_Load("data/image/combat/bouton_fin_tour.png");
    if (att == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface* bouton_sort = IMG_Load("data/image/combat/bouton_sort.png");
    if (att == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() < 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Chargement de la police de caractères
    TTF_Font *font = TTF_OpenFont("data/image/combat/police.ttf", 15);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police de caractères : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //declaration des texture 
    SDL_Texture* Text_Fini =SDL_CreateTextureFromSurface(renderer, Fini);
    SDL_Texture* casetTexture = SDL_CreateTextureFromSurface(renderer, Casetab);
    SDL_Texture* attText = SDL_CreateTextureFromSurface(renderer, att);
    SDL_Texture* bouton_avancerText = SDL_CreateTextureFromSurface(renderer, bouton_avancer);
    SDL_Texture* bouton_fin_tourText = SDL_CreateTextureFromSurface(renderer, bouton_fin_tour);
    SDL_Texture* bouton_sortText = SDL_CreateTextureFromSurface(renderer, bouton_sort);
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    //destruction des surface  
    SDL_FreeSurface(Fini);
    SDL_FreeSurface(att);
    SDL_FreeSurface(Casetab);
    SDL_FreeSurface(backgroundSurface);
    
    int mouseX, mouseY;
    int tour=0;
    int tourmax=0; 
    int action=0;


    pos_t pl;

    tourmax=nombre_Entite(plateau_de_combat);
    turn_order(plateau_de_combat,turn);

    while (FIN==0) {
        SDL_Event event;
          while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX, &mouseY);
                        pl=plateau_cible(mouseX,mouseY,gridX,gridY);
                        if(plateau_de_combat[turn[tour].x][turn[tour].y].equipe==2){
                            if((mouseX >= buttonBottomX && mouseX <= buttonBottomX + BUTTON_SIZEx && mouseY >= buttonBottomY && mouseY <= buttonBottomY + BUTTON_SIZEy) && (action==0)){
                                action=1;
                             }if((mouseX >= buttonBottomX && mouseX <= buttonBottomX + BUTTON_SIZEx && mouseY >= (buttonBottomY - BUTTON_SIZEy) && mouseY <= buttonBottomY) && (action==0)){
                                    action=2;
                             }if((mouseX >= (buttonBottomX - BUTTON_SIZEx) && mouseX <= buttonBottomX && mouseY >= buttonBottomY && mouseY <= buttonBottomY + BUTTON_SIZEy) && ((action==0)|| (action==5))){
                                if(tour < tourmax - 1){
                                    tour+=1;
                                }else{
                                    tour=0;
                                }
                                    action=0;
                             }if((mouseX >= (buttonBottomX - BUTTON_SIZEx) && mouseX <= buttonBottomX && mouseY >= (buttonBottomY - BUTTON_SIZEy) && mouseY <= buttonBottomY) && (action==0)){
                                action=3;
                             }if(action==1 && pl.x!=-1 && pl.y!=-1){
                                attaque_physiqe(plateau_de_combat[turn[tour].x][turn[tour].y].range,plateau_de_combat[turn[tour].x][turn[tour].y].attaque,turn[tour],pl,plateau_de_combat);
                                action=5;
                             }
                             if(action==2 && pl.x!=-1 && pl.y!=-1){
                                attaque_spell(plateau_de_combat[turn[tour].x][turn[tour].y].range,plateau_de_combat[turn[tour].x][turn[tour].y].attaque,turn[tour],pl,plateau_de_combat);
                                action=5;
                             }
                             if(action==3 && pl.x!=-1 && pl.y!=-1){
                                 mouvement_Joueur(plateau_de_combat[turn[tour].x][turn[tour].y].mouv,turn[tour],pl,plateau_de_combat);
                                action=5;  
                             }
                        }
                    break;
                }
            }

        process_enemy_turn(plateau_de_combat, turn, &tour);// fait le tour de l enemie cherche a s aprocher 

        turn_order(plateau_de_combat,turn); // retri le deroulement des tour   

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL); //affiche le fond 
        dessin_plateau(plateau_de_combat,gridX,gridY,casetTexture,buttonRect,renderer); //affiche la grille 
  
        // Dessiner le rectangle superieur
        SDL_Rect topRect = {0, 0, WINDOW_WIDTH, gridY};
        SDL_RenderCopy(renderer, Text_Fini, NULL, &topRect);

        // Dessiner le rectangle inferieur
        SDL_Rect bottomRect = {0, gridY + gridHeight, WINDOW_WIDTH, WINDOW_HEIGHT - gridY - gridHeight};
        SDL_RenderCopy(renderer, Text_Fini, NULL, &bottomRect);

        // Dessiner le rectangle du bouton
        buttonBottom = init_Button(buttonBottomX, buttonBottomY, BUTTON_SIZEx, BUTTON_SIZEy);
        buttonBottom2 = init_Button(buttonBottomX, buttonBottomY - BUTTON_SIZEy, BUTTON_SIZEx, BUTTON_SIZEy);
        buttonBottom3 = init_Button(buttonBottomX - BUTTON_SIZEx, buttonBottomY, BUTTON_SIZEx, BUTTON_SIZEy);
        buttonBottom4 = init_Button(buttonBottomX - BUTTON_SIZEx, buttonBottomY - BUTTON_SIZEy, BUTTON_SIZEx, BUTTON_SIZEy);

        if(action==0){
            draw_Text(renderer, font, "   C'est votre tour   ",gridHeight-BUTTON_SIZEx,0, 2*BUTTON_SIZEx,2*BUTTON_SIZEy,  textColor, bgColor, &statu);
        }
        if(action==1){
            draw_Text(renderer, font, "   attaque un enemie  ",gridHeight-BUTTON_SIZEx,0, 2*BUTTON_SIZEx,2*BUTTON_SIZEy,  textColor, bgColor, &statu);
        }
        if(action==2){
            draw_Text(renderer, font, "   vous aller utiliser un sort  ",gridHeight-BUTTON_SIZEx,0, 2*BUTTON_SIZEx,2*BUTTON_SIZEy,  textColor, bgColor, &statu);
        }if(action==3){
            draw_Text(renderer, font, "   mouvement en  cour  ",gridHeight-BUTTON_SIZEx,0, 2*BUTTON_SIZEx,2*BUTTON_SIZEy, textColor, bgColor, &statu);
        }if(action!=1 && action!=2 && action!=3 && action!=0){
            draw_Text(renderer, font, "   Metter Fin a votre tour  ",gridHeight-BUTTON_SIZEx,0, 2*BUTTON_SIZEx,2*BUTTON_SIZEy, textColor, bgColor, &statu);
        }



        // Remplir le rectangle du bouton
        set_Button_Image(renderer, attText, &buttonBottom.rect);
        set_Button_Image(renderer, bouton_sortText, &buttonBottom2.rect);
        set_Button_Image(renderer, bouton_fin_tourText, &buttonBottom3.rect);
        set_Button_Image(renderer, bouton_avancerText, &buttonBottom4.rect);

        //affiche stat si entite mob cliquer 
        if ((pl.x >= 0 && pl.x < GRID_ROWS) && (pl.y >= 0 && pl.y < GRID_COLUMNS)) {
            if ((action == 0 || action == 5) && (plateau_de_combat[pl.x][pl.y].pv>0)) {
                drawText_With_Stats(renderer, font, plateau_de_combat[pl.x][pl.y].prenom, plateau_de_combat[pl.x][pl.y].classe,plateau_de_combat[pl.x][pl.y].pv,plateau_de_combat[pl.x][pl.y].attaque,0,gridY + gridHeight, 250, 300, textColor, bgColor, &boundingRect);
            }
        }

        //verifie si une equipe a gagner ou non et renvoi la victoire ou defaite pour le joueur (1 = win 0=combat en cour et -1 pour defaite)
        FIN=Fin_De_combat(turn,1,2,plateau_de_combat);

    
    SDL_RenderPresent(renderer); //affiche 
    
    }

    //detruit tout 
    SDL_DestroyTexture(Text_Fini);
    SDL_DestroyTexture(attText);
    SDL_DestroyTexture(casetTexture);
    SDL_DestroyTexture(backgroundTexture);

    return FIN;

}
