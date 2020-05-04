#include <application.h>
#include "header.h"

void ddd();
int main() {
    srand(time(0));

    App *app = get_application();
//    t_entity *player = malloc(sizeof(t_entity));
//    t_entity *not = malloc(sizeof(t_entity));

    init_sdl(app);
//    show_menu(app->renderer);
//    new_player(app, player);
    ddd();
    //    create_note(app->renderer, not->texture);


//    SDL_DestroyTexture(player->texture);
//    SDL_DestroyTexture(not->texture);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();

    return 0;
}
