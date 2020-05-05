#include <fcntl.h>
#include "header.h"

void move_hero(t_hero *hero);

void render_hearts(SDL_Renderer *renderer,
                   const t_entity *game_window, SDL_Rect *heart1,
                   SDL_Rect *heart2, SDL_Rect *heart3, int lives);

void path_for_res_old(const char *file_name, char *path) {
    char *paths[] = {
            "../MUP/endgame/resources/",
            "../resources/",
            "./resources/"};
    for (int i = 0; i < 3; i++) {
        strcpy(path, paths[i]);
        strcat(path, file_name);
        int fd = open(paths[i], O_RDONLY);
        if (fd != -1) {
            close(fd);
            return;
        }
    }
}

void new_player(App *app, t_entity *player, t_entity *game_window) {
    char path[1024];
    path_for_res_old("player.png", path);
    SDL_Surface *surface = IMG_Load(path);
    path_for_res_old("background.png", path);
    SDL_Surface *background = IMG_Load(path);

    if (!surface) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
    }

    if (!background) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
    }

    player->texture1 = SDL_CreateTextureFromSurface(app->renderer, surface);
    player->background = SDL_CreateTextureFromSurface(app->renderer,
                                                      background);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(background);
    if (!player->texture1) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
    }
    if (!player->background) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
    }

//struct to hold the position and size of the sprite
//    SDL_Rect dest;
    SDL_Rect bg;
//get the dimesion of the rectangle
    SDL_QueryTexture(player->background, NULL, NULL, &bg.w, &bg.h);
    bg.w /= 1;
    bg.h /= 1;


// Create hero position
    t_hero hero;
    hero.is_moving = 0;

    SDL_QueryTexture(player->texture1, NULL, NULL, &hero.rect.w, &hero.rect.h);
    hero.rect.w /= 4;
    hero.rect.h /= 4;
    hero.rect.x = (WINDOW_WIDTH - hero.rect.w) / 2;
    hero.rect.y = (WINDOW_WIDTH - hero.rect.w) * 2;

//set to 1 when window close button is pressed
    int close_requested = 0;
    //Start the music
    load_music(player);
    Mix_PlayMusic(player->level_song, -1);

    add_hero_lives_textures(app->renderer, game_window);
    SDL_Rect heart1 = {410, 10, 40, 40};
    SDL_Rect heart2 = {360, 10, 40, 40};
    SDL_Rect heart3 = {310, 10, 40, 40};

    int lives = 6;

    // TODO: create notes state structure
    // t_notes notes = ....

    //animation loop
    while (!close_requested) {
        SDL_Event event;
        SDL_RendererFlip rotate = SDL_FLIP_VERTICAL;
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

        move_hero(&hero);

        // TODO: Move hero rendering to a separate method
        //clear the window
        SDL_RenderClear(app->renderer);

        //draw the image to the window
        SDL_RenderCopy(app->renderer, player->background, NULL, &bg);

        render_hearts(app->renderer, game_window,
                      &heart1, &heart2, &heart3, lives);

        if (hero.direction == RIGHT) {
            SDL_RenderCopy(app->renderer, player->texture1, NULL, &hero.rect);
        } else {
            SDL_RenderCopyEx(app->renderer, player->texture1, NULL, &hero.rect,
                             180.0f, NULL, rotate);
        }
        SDL_RenderPresent(app->renderer);

        // TODO: add notes positions recalculation
        // notes_next(notes);

        // TODO: add notes rendering method
        // notes_render(renderer, notes_textures_array);

        //wait 1/60th of a second
        SDL_Delay(1000 / 60);
    }
    //Mix_FreeMusic(player->level_song);
    //Mix_CloseAudio();
}

void render_hearts(SDL_Renderer *renderer,
                   const t_entity *game_window, SDL_Rect *heart1,
                   SDL_Rect *heart2, SDL_Rect *heart3, int lives) {

    switch (lives) {
        case 6:
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart1);
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart2);
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart3);
            break;
        case 5:
            SDL_RenderCopy(renderer, game_window->texture2, NULL, heart1);
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart2);
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart3);
            break;
        case 4:
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart1);
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart2);
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart3);
            break;
        case 3:
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart1);
            SDL_RenderCopy(renderer, game_window->texture2, NULL, heart2);
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart3);
            break;
        case 2:
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart1);
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart2);
            SDL_RenderCopy(renderer, game_window->texture1, NULL, heart3);
            break;
        case 1:
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart1);
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart2);
            SDL_RenderCopy(renderer, game_window->texture2, NULL, heart3);
            break;
        case 0: //Game over
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart1);
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart2);
            SDL_RenderCopy(renderer, game_window->texture3, NULL, heart3);
            break;
        default:
            break;
    }
}

void move_hero(t_hero *hero) {
    //give sprite initial velocity
    float x_vel = 0;
    if (hero->is_moving != 0) {
        x_vel = hero->direction == LEFT ? -SCROLL_SPEED : SCROLL_SPEED;
    }

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
