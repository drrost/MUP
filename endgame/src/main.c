#include <application.h>
#include "header.h"

int main() {
    srand(time(0));

    App *app = get_application();
    init_sdl(app);


//    t_entity *not = malloc(sizeof(t_entity));
    present_logo_scene();

    int scene = 6;
    while (scene == 3 || scene == 6 || scene == 5) {
        scene = show_menu(app->renderer);
        if (scene == 3) {
            scene = scoreboard(app->renderer);
        }
        if (scene == 5)
            scene = show_about(app->renderer);
    }
    if (scene == 1) {
        t_entity *player = malloc(sizeof(t_entity));
        t_notes *note = (t_notes *)malloc(sizeof(t_notes));
        create_notes(app, note);
        note->nota.n_1.x = init_random(0, 700); 
        note->nenota.n_1.x = init_random(0, 700);

        note->nota.n_2.x = init_random(0, 700);
        note->nenota.n_2.x = init_random(0, 700);

        note->nota.n_3.x = init_random(0, 700);
        note->nenota.n_3.x = init_random(0, 700);
        note->step = 1;
        note->hp = 3;
        new_player(app, player, note);
    }


    // SDL_Delay(1000000);

//    t_entity *not = malloc(sizeof(t_entity));

//    create_note(app->renderer, not->texture);


//    SDL_DestroyTexture(player->texture);
//    SDL_DestroyTexture(not->texture);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
