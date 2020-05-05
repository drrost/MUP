#include "header.h"

void add_hero_lives_textures(
                             SDL_Renderer *renderer, t_hearts *hearts) {
  hearts->full =
    IMG_LoadTexture(renderer, path_for_res("fullheart.png"));
  hearts->half =
    IMG_LoadTexture(renderer, path_for_res("halfheart.png"));
  hearts->empty =
    IMG_LoadTexture(renderer, path_for_res("emptyheart.png"));
  hearts->heart_pos1.x = 410;
  hearts->heart_pos1.y = 10;
  hearts->heart_pos1.w = 40;
  hearts->heart_pos1.h = 40;
  hearts->heart_pos2.x = 360;
  hearts->heart_pos2.y= 10;
  hearts->heart_pos2.w = 40;
  hearts->heart_pos2.h = 40;
  hearts->heart_pos3.x = 310;
  hearts->heart_pos3.y= 10;
  hearts->heart_pos3.w = 40;
  hearts->heart_pos3.h = 40;
}
