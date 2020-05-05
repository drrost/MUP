#include <application.h>
#include "header.h"

int main() {
    srand(time(0));

    App *app = get_application();
    init_sdl(app);

    present_logo_scene();
    int scene = show_menu(app->renderer);
    if (scene == 1) {
    t_entity *player = malloc(sizeof(t_entity));
    new_player(app, player);
    }
    if (scene == 3) {
        scoreboard(app->renderer);
    }

    // SDL_Delay(1000000);

//    t_entity *not = malloc(sizeof(t_entity));

//    create_note(app->renderer, not->texture);


//    SDL_DestroyTexture(player->texture);
//    SDL_DestroyTexture(not->texture);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();

    return 0;
}
