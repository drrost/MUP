//
// Created by Rostyslav Druzhchenko on 04.05.2020.
//

#include <sdl_all.h>
#include <header.h>

void present_logo_scene() {
    SDL_Event event;

    SDL_Renderer *renderer = get_application()->renderer;

    //Customize panels
    SDL_Rect rc_logo = {250, 150, 300, 300};

    const char *path = path_for_res("logo.jpg");
    SDL_Texture *logo = IMG_LoadTexture(renderer, path);

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE ||
                    event.key.keysym.sym == SDLK_RETURN ||
                    event.key.keysym.sym == SDLK_SPACE) {
                    SDL_DestroyTexture(logo);
                    return;
                }
            }
        }
        SDL_RenderCopy(renderer, logo, NULL, &rc_logo);
        usleep(100);
        SDL_RenderPresent(renderer);
    }
}
