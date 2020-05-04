//
// Created by User on 02.05.2020.
//
#ifndef HEADER_H
#define HEADER_H

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)
#define SCROLL_SPEED (300)
#define NOTE_WIDTH (200)
#define NOTE_HEIGHT (200)

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>

#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
//#include <SDL2_mixer/SDL_mixer.h>

//#include <SDL_image.h>
//#include <SDL_ttf.h>

typedef struct Application {
    SDL_Renderer *renderer;
    SDL_Window *window;
//    int left;
//    int right;
//    int quit;
} App;

typedef struct s_entity {
//    int x;
//    int y;
    SDL_Rect *rect;
    SDL_Texture *texture;
    SDL_Texture *background;
} t_entity;

void new_player(App *app, t_entity *player);
void init_sdl(App *app);
t_entity *create_note(SDL_Renderer *renderer, char *texture);
void cleanup(App *app);
void note_falling(t_entity *note, int *level, int *score);
int show_menu(SDL_Renderer *renderer);

#endif
