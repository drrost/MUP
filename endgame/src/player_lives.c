#include "header.h"

t_entity add_hero_lives_textures(
        SDL_Renderer *renderer, t_entity *game_window) {
  game_window->texture =
          IMG_LoadTexture(renderer, path_for_res("fullheart.png"));
  return *game_window;
}
