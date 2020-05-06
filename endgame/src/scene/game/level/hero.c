//
// Created by Rostyslav Druzhchenko on 06.05.2020.
//

#include <hero.h>
#include <header.h>

t_hero *create_hero(SDL_Renderer *renderer) {
    t_hero *hero = (t_hero *) malloc(sizeof(t_hero));
    hero->is_moving = 0;
    hero->texture = IMG_LoadTexture(renderer, MX_RES("player.png"));

    return hero;
}

void destroy_hero(t_hero **hero) {
    SDL_DestroyTexture((*hero)->texture);
    free(*hero);
    *hero = 0;
}
