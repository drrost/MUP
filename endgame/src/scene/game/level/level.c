//
// Created by Rostyslav Druzhchenko on 06.05.2020.
//

#include <level.h>
#include <stdlib.h>

t_level *create_level(SDL_Renderer *renderer) {
    t_level *level = (t_level *) malloc(sizeof(t_level));
    level->renderer = renderer;

    level->background = create_sprite(renderer, "background.png");
    level->background->rect = (SDL_Rect) {0, 0, 800, 600};

    level->hero = create_hero(renderer);

    return level;
}

void destroy_level(t_level **level) {
    destroy_sprite(&((*level)->background));
    destroy_hero(&((*level)->hero));
    free(*level);
    *level = 0;
}
