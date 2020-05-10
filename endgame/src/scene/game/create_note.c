#include "header.h"

void create_notes(SDL_Renderer *renderer, t_notes *note) {
    note->nota.texture = IMG_LoadTexture(renderer, MX_RES("nota.png"));
    note->nenota.texture = IMG_LoadTexture(renderer, MX_RES("nenota.png"));

    SDL_QueryTexture(note->nota.texture, NULL, NULL, &(note->nota.n_1.w),
                     &(note->nota.n_1.h));
    SDL_QueryTexture(note->nenota.texture, NULL, NULL, &(note->nenota.n_1.w),
                     &note->nenota.n_1.h);
    SDL_QueryTexture(note->nota.texture, NULL, NULL, &note->nota.n_2.w,
                     &note->nota.n_2.h);
    SDL_QueryTexture(note->nenota.texture, NULL, NULL, &note->nenota.n_2.w,
                     &note->nenota.n_2.h);
    SDL_QueryTexture(note->nota.texture, NULL, NULL, &note->nota.n_3.w,
                     &note->nota.n_3.h);
    SDL_QueryTexture(note->nenota.texture, NULL, NULL, &note->nenota.n_3.w,
                     &note->nenota.n_3.h);
}
