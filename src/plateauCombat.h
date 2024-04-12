
#include <combatcomun.h>


int nombre_Entite(entite_t plateau[N][N]);

void init_plateau(entite_t plateau[N][N]);

void dessin_plateau(entite_t plateau_de_combat[N][N],int gridX,int gridY, SDL_Texture* rien,Button buttonRect,SDL_Renderer* renderer);

int FinDecombat(pos_t turn[N*N], int EquipeGagnante, int EquipePerdant, entite_t plateau[N][N]);