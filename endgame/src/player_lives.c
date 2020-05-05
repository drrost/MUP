#include "header.h"

t_entity add_hero_lives_textures(
        SDL_Renderer *renderer, t_entity *game_window) {
  game_window->texture1 =
          IMG_LoadTexture(renderer, path_for_res("fullheart.png"));
  game_window->texture2 =
    IMG_LoadTexture(renderer, path_for_res("halfheart.png"));
  game_window->texture3 =
    IMG_LoadTexture(renderer, path_for_res("emptyheart.png"));
  return *game_window;
}
