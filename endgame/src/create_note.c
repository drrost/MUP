#include "header.h"

static void mx_printerror(char *str) {
	write(2, "endgame: ", 9);
	for (int i = 0; str[i] != '\0'; i++)
		write(2, &str[i], 1);
	write(2, "\n", 1);
}

static void sdlerror(void) {
	mx_printerror((char*)SDL_GetError());
	exit(2);
}

void create_notes(t_notes *note) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		sdlerror();
	note->w = 800;
	note->h = 600;
	note->window = SDL_CreateWindow("Notes", SDL_WINDOWPOS_CENTERED, 
								 SDL_WINDOWPOS_CENTERED, note->w, note->h, 
								 SDL_WINDOW_ALLOW_HIGHDPI);
	if (note->window == NULL) 
	    sdlerror();
	if ((note->win_srfc = SDL_GetWindowSurface(note->window)) == NULL)// головний сурфейс
		sdlerror();
	if ((note->wlpp = IMG_Load("./resources/background.png")) == NULL)//заставка
		sdlerror();
	if ((note->player.srf = IMG_Load("./resources/player.png")) == NULL)
		sdlerror();
	if ((note->nota.srf = IMG_Load("./resources/nota.png")) == NULL)
		sdlerror();
	if ((note->nenota.srf = IMG_Load("./resources/nenota.png")) == NULL)
		sdlerror();
	if ((note->heart.srf = IMG_Load("./resources/heart.png")) == NULL)
		sdlerror();
	note->player.n_1.y = 550;						// опустили player по у
	if(TTF_Init() == -1)
		sdlerror();
}
