#include <fcntl.h>
#include "header.h"

void path_for_res_old(const char *file_name, char *path) {
    char *paths[] = {
            "../MUP/endgame/resources/",
            "../resources/",
            "./resources/" };
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

void new_player(App *app, t_entity *player, t_entity *game_window, t_notes *note) {
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

    player->texture = SDL_CreateTextureFromSurface(app->renderer, surface);
    player->background = SDL_CreateTextureFromSurface(app->renderer,
                                                      background);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(background);
    if (!player->texture) {
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
    SDL_Rect dest;
    SDL_Rect bg;
//get the dimesion of the rectangle
    SDL_QueryTexture(player->background, NULL, NULL, &bg.w, &bg.h);
    bg.w /= 1;
    bg.h /= 1;
    SDL_QueryTexture(player->texture, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 4;
    dest.h /= 4;

//start sprite  in the center of screen
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) * 2;
//give sprite initial velocity
    float x_vel = 0;
    float y_vel = 0;

//keep track of which inputs are given
    int left = 0;
    int right = 0;

//set to 1 when window close button is pressed
    int close_requested = 0;
    //Start the music
    load_music(player);
    Mix_PlayMusic(player->level_song, -1);

    player_lives(app, game_window);
    SDL_Rect fullheart1 = {410, 10, 40, 40};
    SDL_Rect fullheart2= {360, 10, 40, 40};
    SDL_Rect fullheart3= {310, 10, 40, 40};

    //animation loop
    while (!close_requested) {
        SDL_Event event;
	int flip;
	float angle = 180.0f; //set the angle
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
                            left = 1;
			    flip = 1;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right = 1;
			    flip = 0;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            left = 0;
                            break;;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right = 0;
                            break;
                        default:
                            break;

                    }
                    break;
            }

            //forever loop noty i nenoty
            bool on = 1;
            int x;
            while (on == 1) {
                while (SDL_PollEvent(&event)) {
                    x = event.motion.x;                     //позиция мышки по х
                    int key = event.key.keysym.sym;
                    if (event.type == SDL_QUIT)             //условия выхода с программы
                        on = 0;
                    if (event.type == SDL_KEYDOWN && key == SDLK_ESCAPE) //условия выхода с программы
                        on = 0;
                }
                if (note->hp > 0)
                    note_falling(note, x);
                print_window(note);
            }
            SDL_FreeSurface(note->win_srfc);
            SDL_DestroyWindow(note->window);
            TTF_CloseFont(note->font);
            TTF_Quit();
            SDL_Quit();
        }
        //determine velocity
        x_vel = y_vel = 0;
        if (left && !right) x_vel = -SCROLL_SPEED;
        if (right && !left) x_vel = SCROLL_SPEED;

        //update positions;
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        //collision detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
        if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;

        //set the position in the struct
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;

        //clear the window
        SDL_RenderClear(app->renderer);

        //draw the image to the window
	SDL_RenderCopy(app->renderer, player->background, NULL, &bg);
	SDL_RenderCopy(app->renderer, game_window->texture, NULL, &fullheart1);
	SDL_RenderCopy(app->renderer, game_window->texture, NULL, &fullheart2);
	SDL_RenderCopy(app->renderer, game_window->texture, NULL, &fullheart3);
        //SDL_RenderCopy(app->renderer, player->background, NULL, &bg);
	if (flip != 1) {
	  SDL_RenderCopy(app->renderer, player->texture, NULL, &dest);
	} else {
	  SDL_RenderCopyEx(app->renderer, player->texture, NULL, &dest, angle, NULL, rotate);
	}
        SDL_RenderPresent(app->renderer);

        //wait 1/60th of a second
        SDL_Delay(1000 / 60);
    }
    //Mix_FreeMusic(player->level_song);
    //Mix_CloseAudio();
}
