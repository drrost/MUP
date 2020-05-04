//
// Created by User on 03.05.2020.
//
#include "../inc/header.h"

void initSDL(App *app, t_entity *player, t_entity *not) {
    not++;    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    app->window = SDL_CreateWindow("Notes", 0, 0, WINDOW_WIDTH,
                                   WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!app->window) {
        printf("Failed to open %d x %d window: %s\n", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_GetError());
        exit(1);
    }
    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!app->renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
//    createNote(app->renderer, not->texture);
    SDL_ShowCursor (0);
    int process = show_menu(app->renderer);
    if (process == 1) {
            newPlayer(app, player);
    }

}
