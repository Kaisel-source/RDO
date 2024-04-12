#include <Bouton.h>



Button initButton(int x, int y, int width, int height) {
    Button button;
    button.rect.x = x;
    button.rect.y = y;
    button.rect.w = width;
    button.rect.h = height;
    return button;
}

/**
 * @brief retoune un espace defenie sous la forme d un rectangle 
 * 
 * @param bouttonx 
 * @param bouttony 
 * @return SDL_Rect 
 */
SDL_Rect getButtonRect(int bouttonx, int bouttony) {
    Button buttonRect;
    buttonRect.rect.x = bouttonx;
    buttonRect.rect.y = bouttony;
    buttonRect.rect.w = BUTTON_SIZEx;
    buttonRect.rect.h = BUTTON_SIZEy;
    
    return buttonRect.rect;
}


/**
 * @brief colle une img sur un espace defini
 * 
 * @param renderer 
 * @param imageTexture 
 * @param buttonRect 
 */
void setButtonImage(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect) {
    SDL_RenderCopy(renderer, imageTexture, NULL, buttonRect);
}