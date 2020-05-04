#include "header.h"
#include <stdbool.h>

void
draw_text(SDL_Color color, int x, int y, char *text, SDL_Renderer *renderer,
          TTF_Font *font) {
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *textureGameName = SDL_CreateTextureFromSurface(renderer,
                                                                text_surface);
    SDL_Rect text_rect = {x, y, 1, 1};
    SDL_QueryTexture(textureGameName, NULL, NULL, &text_rect.w, &text_rect.h);
    SDL_RenderCopy(renderer, textureGameName, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    text_surface = 0;
    SDL_DestroyTexture(textureGameName);
}

int show_menu(SDL_Renderer *renderer) {
    bool running = true;
    SDL_Event event;
    int index_menu = 1;
    TTF_Init();
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }
    TTF_Font *font = TTF_OpenFont(path_for_res("ARIAL.TTF"), 25);
    SDL_Color color = {0, 0, 255, 0};

    //Customize panels
    SDL_Rect button1 = {280, 100, 240, 50};
    SDL_Texture *button11 =
            IMG_LoadTexture(renderer, path_for_res("empty.png"));
    SDL_Rect button2 = {280, 165, 240, 50};
    SDL_Texture *button22 =
            IMG_LoadTexture(renderer, path_for_res("empty.png"));
    SDL_Rect button3 = {280, 230, 240, 50};
    SDL_Texture *button33 =
            IMG_LoadTexture(renderer, path_for_res("empty.png"));
    SDL_Rect button4 = {280, 295, 240, 50};
    SDL_Texture *button44 =
            IMG_LoadTexture(renderer, path_for_res("empty.png"));
    SDL_Rect button5 = {280, 360, 240, 50};
    SDL_Texture *button55 =
            IMG_LoadTexture(renderer, path_for_res("empty.png"));

    //background
    SDL_Rect backgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Texture *imgBackground =
            IMG_LoadTexture(renderer, path_for_res("empty_back.png"));

    while (running) {
        color.r = 0;
        color.g = 255;
        color.b = 255;
        color.a = 0;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return 0;
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    if (index_menu == 2) index_menu = 1;
                    if (index_menu == 3) index_menu = 2;
                    if (index_menu == 4) index_menu = 3;
                    if (index_menu == 5) index_menu = 4;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    if (index_menu == 4) index_menu = 5;
                    if (index_menu == 3) index_menu = 4;
                    if (index_menu == 2) index_menu = 3;
                    if (index_menu == 1) index_menu = 2;
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    return index_menu;
                }
            }
        }
        SDL_RenderCopy(renderer, imgBackground, NULL, &backgroundRect);
        SDL_RenderCopy(renderer, button11, NULL, &button1);
        SDL_RenderCopy(renderer, button22, NULL, &button2);
        SDL_RenderCopy(renderer, button33, NULL, &button3);
        SDL_RenderCopy(renderer, button44, NULL, &button4);
        SDL_RenderCopy(renderer, button55, NULL, &button5);
        if (index_menu == 1) {
            color.g = 0;
            draw_text(color, 360, 110, "START", renderer, font);
            color.g = 255;
            draw_text(color, 350, 175, "PLAYER", renderer, font);
            draw_text(color, 345, 240, "SCORES", renderer, font);
            draw_text(color, 370, 305, "QUIT", renderer, font);
            draw_text(color, 360, 370, "ABOUT", renderer, font);
        } else if (index_menu == 2) {
            color.g = 0;
            draw_text(color, 350, 175, "PLAYER", renderer, font);
            color.g = 255;
            draw_text(color, 345, 240, "SCORES", renderer, font);
            draw_text(color, 370, 305, "QUIT", renderer, font);
            draw_text(color, 360, 370, "ABOUT", renderer, font);
            draw_text(color, 360, 110, "START", renderer, font);
        } else if (index_menu == 3) {
            color.g = 0;
            draw_text(color, 345, 240, "SCORES", renderer, font);
            color.g = 255;
            draw_text(color, 370, 305, "QUIT", renderer, font);
            draw_text(color, 360, 370, "ABOUT", renderer, font);
            draw_text(color, 360, 110, "START", renderer, font);
            draw_text(color, 350, 175, "PLAYER", renderer, font);
        } else if (index_menu == 4) {
            color.g = 0;
            draw_text(color, 370, 305, "QUIT", renderer, font);
            color.g = 255;
            draw_text(color, 360, 370, "ABOUT", renderer, font);
            draw_text(color, 360, 110, "START", renderer, font);
            draw_text(color, 350, 175, "PLAYER", renderer, font);
            draw_text(color, 345, 240, "SCORES", renderer, font);
        } else if (index_menu == 5) {
            color.g = 0;
            draw_text(color, 360, 370, "ABOUT", renderer, font);
            color.g = 255;
            draw_text(color, 360, 110, "START", renderer, font);
            draw_text(color, 350, 175, "PLAYER", renderer, font);
            draw_text(color, 345, 240, "SCORES", renderer, font);
            draw_text(color, 370, 305, "QUIT", renderer, font);
        }
        usleep(100);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(imgBackground);

    return 1;
}
