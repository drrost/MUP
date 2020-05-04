#include <application.h>
#include "header.h"

int main() {
    srand(time(0));

    App *app = get_application();
//    t_entity *not = malloc(sizeof(t_entity));

    init_sdl(app);
//    show_menu(app->renderer);
//    present_logo_scene();
    //    create_note(app->renderer, not->texture);

    t_entity *player = malloc(sizeof(t_entity));
    new_player(app, player);

//    SDL_DestroyTexture(player->texture);
//    SDL_DestroyTexture(not->texture);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();

    return 0;
}
