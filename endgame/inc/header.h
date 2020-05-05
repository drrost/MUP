#ifndef HEADER_H
#define HEADER_H

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)
#define SCROLL_SPEED (300)
#define NOTE_WIDTH (200)
#define NOTE_HEIGHT (200)

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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
    SDL_Texture *texture1;
  SDL_Texture *texture2;
  SDL_Texture *texture3;
    SDL_Texture *background;
    Mix_Music *level_song;
} t_entity;

enum e_direction {
    LEFT,
    RIGHT
};

typedef struct s_hero {
    enum e_direction direction;
    bool is_moving;
    SDL_Point position;
}              t_hero;

void init_sdl(App *app);
void load_music(t_entity *player);
t_entity *create_note(SDL_Renderer *renderer, char *texture);
void cleanup(App *app);
void note_falling(t_entity *note, int *level, int *score);
const char *path_for_res(const char *file_name);
void draw_text(SDL_Color color, int x, int y, char *text, SDL_Renderer *renderer, TTF_Font *font);
// void draw_the_text(SDL_Color color, int x, int y, char *text, SDL_Renderer *renderer, TTF_Font *font);

// Scenes
int scoreboard(SDL_Renderer *renderer);
void new_player(App *app, t_entity *player, t_entity *game_window);
int show_menu(SDL_Renderer *renderer);
void present_logo_scene();
t_entity add_hero_lives_textures(SDL_Renderer *renderer, t_entity *game_window);

//Other
char *mx_strnew(const int size);

#endif
