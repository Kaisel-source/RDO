#include "../../include/menu/button.h"

Button create_Button(int x, int y, SDL_Texture *texture) {
    Button button;
    button.rect.x = x;
    button.rect.y = y;
    button.rect.w = BUTTON_WIDTH;
    button.rect.h = BUTTON_HEIGHT;
    button.texture = texture;
    return button;
}

void render_Button(Button button, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, button.texture, NULL, &button.rect);
}
