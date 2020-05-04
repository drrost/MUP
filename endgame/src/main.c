#include "../inc/header.h"

int main() {
    App *app = malloc(sizeof(App));
    t_entity *player = malloc(sizeof(t_entity));
    t_entity *not = malloc(sizeof(t_entity));

    initSDL(app, player, not);
    
	SDL_RenderPresent(app->renderer);
//    SDL_DestroyTexture(player->texture);
//    SDL_DestroyTexture(not->texture);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
