
#include <combatcomun.h>




void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int maxWidth, int maxHeight, int lineHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);



void drawTextWithStats(SDL_Renderer *renderer, TTF_Font *font,char *name,char *classe, int pv, int force, int x, int y, int maxWidth, int maxHeight, int lineHeight, SDL_Color textColor, SDL_Color bgColor, SDL_Rect *boundingRect);