//
// Created by Rostyslav Druzhchenko on 09.05.2020.
//

#include <header.h>

t_sprite *create_sprite(SDL_Renderer *renderer, const char *file_name) {
    t_sprite *sprite;
    sprite = (t_sprite *) malloc(sizeof(sprite));
    sprite->texture = IMG_LoadTexture(renderer, MX_RES(file_name));;
    return sprite;
}

void destroy_sprite(t_sprite **sprite) {
    SDL_DestroyTexture((*sprite)->texture);
    free(*sprite);
    *sprite = 0;
}
