#include <application.h>
#include "header.h"

int main() {
    srand(time(0));

    App *app = get_application();
    init_sdl(app);

    present_logo_scene();
    int scene = 6;
    while (scene == 3 || scene == 6 || scene == 5) {
        scene = show_menu(app->renderer);
        if (scene == 3) {
            scene = scoreboard(app->renderer);
        }
        // if (scene == 5)
        //     scene = about;
    }
    if (scene == 1) {
        t_entity *player = malloc(sizeof(t_entity));
        new_player(app, player);
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
