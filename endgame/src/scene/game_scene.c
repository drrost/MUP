#include <hero.h>
#include "header.h"

void move_hero(t_hero *hero);

void render_hearts(SDL_Renderer *renderer, t_hearts *hearts, int lives);
void render_score(SDL_Renderer *renderer, t_score *score, int current_score, bool free);
void render_hero(SDL_Renderer *renderer, SDL_Texture *texture, t_hero *hero);

void new_player(App *app, t_entity *player) {
    SDL_Surface *background = IMG_Load(MX_RES("background.png"));

    if (!background) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
    }

    player->background = SDL_CreateTextureFromSurface(
            app->renderer, background);
    SDL_FreeSurface(background);
    if (!player->background) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
    }

//struct to hold the position and size of the sprite
    SDL_Rect bg;
//get the dimesion of the rectangle
    SDL_QueryTexture(player->background, NULL, NULL, &bg.w, &bg.h);
    bg.w /= 1;
    bg.h /= 1;

// Create hero position
    t_hero hero;
    hero.is_moving = 0;

    hero.texture = IMG_LoadTexture(app->renderer, MX_RES("player.png"));
    SDL_QueryTexture(hero.texture, NULL, NULL, &hero.rect.w, &hero.rect.h);
    hero.rect.w /= 4;
    hero.rect.h /= 4;
    hero.rect.x = (WINDOW_WIDTH - hero.rect.w) / 2;
    hero.rect.y = (WINDOW_WIDTH - hero.rect.w) * 2;

//set to 1 when window close button is pressed
    int close_requested = 0;
    //Start the music
    load_music(player);
    Mix_PlayMusic(player->level_song, -1);
    t_score score;
    show_score(app->renderer, &score);

    t_hearts hearts;
    add_hero_lives_textures(app->renderer, &hearts);

    int lives = 6;
    int current_score = 0;
    int prev_score = 0;
    // TODO: create notes state structure
    // t_notes notes = ....

    //animation loop
    while (!close_requested) {
        SDL_Event event;
	prev_score = current_score;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close_requested = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            hero.is_moving = 1;
                            hero.direction = LEFT;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            hero.direction = RIGHT;
                            hero.is_moving = 1;
                            break;
                        case SDL_SCANCODE_SPACE:
                            lives--;
			    break;
		    case SDL_SCANCODE_TAB:
                      current_score++;
                      break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            hero.is_moving = 0;
                            break;;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            hero.is_moving = 0;
                            break;
                        default:
                            break;

                    }
                    break;
            }
        }

        // MOVE
        //
        move_hero(&hero);
        // TODO: add notes positions recalculation
        // notes_next(notes);

        // RENDER
        //
        //clear the window
        SDL_RenderClear(app->renderer);

        //draw the image to the window
        SDL_RenderCopy(app->renderer, player->background, NULL, &bg);
	prev_score != current_score ? render_score(app->renderer, &score, current_score, true)
	  : render_score(app->renderer, &score, current_score, false);
        render_hearts(app->renderer, &hearts, lives);
        render_hero(app->renderer, hero.texture, &hero);

        // TODO: add notes rendering method
        // notes_render(renderer, notes_textures_array);

        SDL_RenderPresent(app->renderer);

        //wait 1/60th of a second
        SDL_Delay(1000 / 60);
    }
    //Mix_FreeMusic(player->level_song);
    //Mix_CloseAudio();
}

void render_hero(SDL_Renderer *renderer, SDL_Texture *texture, t_hero *hero) {
    if ((*hero).direction == RIGHT) {
        SDL_RenderCopy(renderer, texture, NULL, &(*hero).rect);
    } else {
        SDL_RenderCopyEx(renderer, texture, NULL, &(*hero).rect,
                         180.0f, NULL, SDL_FLIP_VERTICAL);
    }
}

void render_score(SDL_Renderer *renderer, t_score *score, int current_score, bool free){
  if (free){
    SDL_DestroyTexture(score->texture2);
  }
  //TTF_Font *font = TTF_OpenFont(RES("ARIAL.TTF"), 20);                                                                                                                       
  char print[100];
  sprintf(print, "%d", current_score);
  SDL_Surface *to_print = TTF_RenderText_Solid(score->font, print, score->color);
  score->texture2 = SDL_CreateTextureFromSurface(renderer, to_print);
  SDL_FreeSurface(to_print);
  SDL_RenderCopy(renderer, score->texture1, NULL, &score->score_rect);
  SDL_RenderCopy(renderer, score->texture2, NULL, &score->current_score_rect);
}

void render_hearts(SDL_Renderer *renderer, t_hearts *hearts, int lives) {
    switch (lives) {
        case 6:
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos1);
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos2);
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos3);
            break;
        case 5:
            SDL_RenderCopy(renderer, hearts->half, NULL, &hearts->heart_pos1);
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos2);
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos3);
            break;
        case 4:
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos1);
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos2);
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos3);
            break;
        case 3:
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos1);
            SDL_RenderCopy(renderer, hearts->half, NULL, &hearts->heart_pos2);
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos3);
            break;
        case 2:
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos1);
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos2);
            SDL_RenderCopy(renderer, hearts->full, NULL, &hearts->heart_pos3);
            break;
        case 1:
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos1);
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos2);
            SDL_RenderCopy(renderer, hearts->half, NULL, &hearts->heart_pos3);
            break;
        case 0: //Game over
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos1);
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos2);
            SDL_RenderCopy(renderer, hearts->empty, NULL, &hearts->heart_pos3);
            break;
        default:
            break;
    }
}

void move_hero(t_hero *hero) {
    //give sprite initial velocity
    float x_vel = 0;
    if (hero->is_moving != 0)
        x_vel = hero->direction == LEFT ? -SCROLL_SPEED : SCROLL_SPEED;

    //update positions;
    hero->rect.x += x_vel / 60;

    //collision detection with bounds
    if (hero->rect.x <= 0) hero->rect.x = 0;
    if (hero->rect.y <= 0) hero->rect.y = 0;
    if (hero->rect.x >= WINDOW_WIDTH - hero->rect.w)
        hero->rect.x = WINDOW_WIDTH - hero->rect.w;
    if (hero->rect.y >= WINDOW_HEIGHT - hero->rect.h)
        hero->rect.y = WINDOW_HEIGHT - hero->rect.h;
}
