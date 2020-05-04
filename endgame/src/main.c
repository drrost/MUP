#include "header.h"

int main() {
    App *app = malloc(sizeof(App));
    t_entity *player = malloc(sizeof(t_entity));
//    t_entity *not = malloc(sizeof(t_entity));
    t_notes *note = (t_notes *)malloc(sizeof(t_notes));
    create_notes(note);

    init_sdl(app);

    note->nota.n_1.x = init_random(0, 800);  // рандомное начало для выпадания элементов
    note->nenota.n_1.x = init_random(0, 800);

    note->nota.n_2.x = init_random(0, 800);
    note->nenota.n_2.x = init_random(0, 800);

    note->nota.n_3.x = init_random(0, 800);
    note->nenota.n_3.x = init_random(0, 800);
    note->hp = 14;
    note->score = 0;
    note->step = 1;

    print_window(note);


//    show_menu(app->renderer);
    new_player(app, player, note);
    //    create_note(app->renderer, not->texture);

    SDL_RenderPresent(app->renderer);
//    SDL_DestroyTexture(player->texture);
//    SDL_DestroyTexture(not->texture);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
