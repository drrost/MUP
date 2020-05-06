#include <hero.h>
#include <level.h>
#include "header.h"

void move_hero(t_hero *hero);
void render_hearts(SDL_Renderer *renderer, t_hearts *hearts, int lives);
void render_score(
        SDL_Renderer *renderer, t_score *score, int current_score, bool free);
void render_hero(SDL_Renderer *renderer, SDL_Texture *texture, t_hero *hero);

void present_game_scene(App *app, t_entity *player, t_notes *note) {

    SDL_Surface *background = IMG_Load(MX_RES("background.png"));
    player->background =
            SDL_CreateTextureFromSurface(app->renderer, background);
    SDL_FreeSurface(background);

//struct to hold the position and size of the sprite
    SDL_Rect bg;
//get the dimesion of the rectangle
    SDL_QueryTexture(player->background, NULL, NULL, &bg.w, &bg.h);
    bg.h /= 1;
    bg.w /= 1;

// Create hero position
    t_level *level = create_level(app->renderer);
    t_hero *hero = level->hero;
    hero->is_moving = 0;

//set to 1 when window close button is pressed
    int close_requested = 0;
    //Start the music
    load_music(player);
    Mix_PlayMusic(player->level_song, -1);


    SDL_Surface *game_over = IMG_Load(MX_RES("game_over.png"));
    SDL_Texture * gameover = SDL_CreateTextureFromSurface(app->renderer, game_over);
    SDL_FreeSurface(game_over);
    SDL_Surface *winwin = IMG_Load(MX_RES("you_win.png"));
    SDL_Texture * win = SDL_CreateTextureFromSurface(app->renderer, winwin);
    SDL_FreeSurface(winwin);

    //t_score score;
    //show_score(app->renderer, &score);

    t_hearts hearts;
    add_hero_lives_textures(app->renderer, &hearts);

    int lives = 6;
    int current_score = 0;
    int prev_score = 0;
    // TODO: create notes state structure
    // t_notes notes = ....
    t_score score;
    show_score(app->renderer, &score);
    //animation loop
    while (!close_requested) {
        SDL_Event event;

        note_falling(note);

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
                            hero->is_moving = 1;
                            hero->direction = LEFT;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            hero->direction = RIGHT;
                            hero->is_moving = 1;
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
                            hero->is_moving = 0;
                            break;;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            hero->is_moving = 0;
                            break;
                        case SDL_SCANCODE_Q:
                            Mix_FreeMusic(player->level_song);
                            destroy_level(&level);
                            return;
                        default:
                            break;
                    }
                    break;
            }
        }

        // MOVE
        //
        move_hero(hero);

        // RENDER
        //
        //clear the window
        SDL_RenderClear(app->renderer);

        //draw the image to the window
	if (lives <= 0) {
	  SDL_RenderCopy(app->renderer, gameover, NULL, NULL);
	  close_requested = 1;
        } else if (current_score >= 20) {
          SDL_RenderCopy(app->renderer, win, NULL, NULL);
          close_requested = 1;
        } else {
	  SDL_RenderCopy(app->renderer, player->background, NULL, &bg);
	  prev_score != current_score ? render_score(app->renderer, &score,
						     current_score, true)
	    : render_score(app->renderer, &score,
			   current_score, false);
	  render_hearts(app->renderer, &hearts, lives);
	  render_hero(app->renderer, hero->texture, hero);
	  print_notes(app, note);
	}

        SDL_RenderPresent(app->renderer);

        //wait 1/60th of a second
        SDL_Delay(1000 / 60);
    }
    SDL_Delay(5000);
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

void render_score(SDL_Renderer *renderer, t_score *score, int current_score,
                  bool free) {
    if (free) {
        SDL_DestroyTexture(score->texture2);
    }
    char print[100];
    sprintf(print, "%d", current_score);
    SDL_Surface *to_print = TTF_RenderText_Solid(score->font, print,
                                                 score->color);
    score->texture2 = SDL_CreateTextureFromSurface(renderer, to_print);
    SDL_FreeSurface(to_print);
    SDL_RenderCopy(renderer, score->texture1, NULL, &score->score_rect);
    SDL_RenderCopy(renderer, score->texture2, NULL,
                   &score->current_score_rect);
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
