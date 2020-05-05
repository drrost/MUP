#include <application.h>
#include "header.h"

int main() {
    srand(time(0));

    App *app = get_application();
    init_sdl(app);

    present_logo_scene();
    show_menu(app->renderer);

    t_entity *player = malloc(sizeof(t_entity));
    t_entity *game_window = malloc(sizeof(t_entity));
    new_player(app, player, game_window);

//    t_entity *not = malloc(sizeof(t_entity));

//    create_note(app->renderer, not->texture);


//    SDL_DestroyTexture(player->texture);
//    SDL_DestroyTexture(not->texture);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();

    return 0;
}
