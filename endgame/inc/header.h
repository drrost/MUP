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
#include <fcntl.h>
#include <errno.h>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

/*typedef struct Application {
    SDL_Renderer *renderer;
    SDL_Window *window;
//    int left;
//    int right;
//    int quit;
} App;*/

typedef struct s_entity {
//    int x;
//    int y;
    SDL_Rect *rect;
    SDL_Texture *texture;
    SDL_Texture *background;
    Mix_Music *level_song;
} t_entity;

typedef struct s_img {
    SDL_Surface *srf;
    SDL_Rect n_1;
    SDL_Rect n_2;
    SDL_Rect n_3;
}               t_img;

typedef struct s_notes {
    SDL_Window *window;
    SDL_Surface *win_srfc; //главний сурфейс
    SDL_Surface *wlpp; //картинка заставка
    SDL_Surface *txt;  // для подсчета чисел
    SDL_Surface *game_over;  // для game over
    TTF_Font *font;
    Mix_Music *music;

    int     w;
    int     h;
    int     hp;
    int     score;
    int     step;

    t_img nota;
    t_img nenota;
    t_img player;
    t_img heart;
} t_notes;


int init_random(int low, int high);
SDL_Rect set_coordinate(SDL_Rect rct, int speed);
bool compare(SDL_Rect a, SDL_Rect b);
void is_catch_note(t_notes *note);
void note_falling(t_notes *note, int x);
void print_heart_score(t_notes *note);
void init_sdl(App *app);
void draw_text(SDL_Color color, int x, int y, char *text, 
               SDL_Renderer *renderer, TTF_Font *font);
void print_window(t_notes *note);
void create_notes(t_notes *note);
void load_music(t_entity *player);
void cleanup(App *app);
void note_falling(t_entity *note, int *level, int *score);
const char *path_for_res(const char *file_name);

// Senes
void new_player(App *app, t_entity *player, t_entity *game_window, t_notes *note);
int show_menu(SDL_Renderer *renderer);
void present_logo_scene();
t_entity player_lives(App *app, t_entity *game_window);

int main();

#endif
