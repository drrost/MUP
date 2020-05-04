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
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <sdl_all.h>
#include <application.h>

typedef struct s_entity {
//    int x;
//    int y;
    SDL_Rect *rect;
    SDL_Texture *texture;
    SDL_Texture *background;
    Mix_Music *level_song;
} t_entity;

void init_sdl(App *app);
void load_music(t_entity *player);
t_entity *create_note(SDL_Renderer *renderer, char *texture);
void cleanup(App *app);
void note_falling(t_entity *note, int *level, int *score);
const char *path_for_res(const char *file_name);

// Senes
void new_player(App *app, t_entity *player, t_entity *game_window);
int show_menu(SDL_Renderer *renderer);
void present_logo_scene();
t_entity player_lives(App *app, t_entity *game_window);

#endif
