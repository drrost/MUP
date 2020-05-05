#include "header.h"

t_entity player_lives(App *app, t_entity *game_window) {
  //char path[1024];
  //path_for_res("fullheart.PNG");
  game_window->texture = IMG_LoadTexture(app->renderer, "../resources/fullheart.png");
  return *game_window;
}
