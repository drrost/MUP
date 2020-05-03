//
// Created by User on 03.05.2020.
//

#include "header.h"

void newPlayer(App *app, t_entity *player) {
//load the image into memory using SDL library function
    SDL_Surface *surface = IMG_Load("../src/player.png");
    SDL_Surface *background = IMG_Load("../src/background.png");
    if (!surface) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
//           /return NULL;
    }

    if (!background) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
//           /return NULL;
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
        //return 1;
    }
    if (!player->background) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        //return 1;
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

//    //start background
//    float bg_x = (WINDOW_WIDTH - bg.w) / 2;
//    float bg_y = (WINDOW_HEIGHT - bg.h) / 2;

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

    //animation loop
    while (!close_requested) {
        SDL_Event event;
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
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right = 1;
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


//    //set the background in the struct;
//    dest.y = (int) y_pos;
//    dest.x = (int) x_pos;
        //clear the window
        SDL_RenderClear(app->renderer);

        //draw the image to the window
        SDL_RenderCopy(app->renderer, player->background, NULL, &bg);
        SDL_RenderCopy(app->renderer, player->texture, NULL, &dest);
        SDL_RenderPresent(app->renderer);

        //wait 1/60th of a second
        SDL_Delay(1000 / 60);
    }
}
