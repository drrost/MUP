#include "header.h"

void print_heart_score(t_notes *note) {
	note->heart.n_1 = note->heart.srf->clip_rect;
	for (int i = 0; i < note->hp; i++) {
		SDL_BlitSurface(note->heart.srf, NULL, note->win_srfc, &note->heart.n_1); // print heart
		note->heart.n_1.x += 45;
	}
	char str[30];
	SDL_Color color = { 55, 255, 55, 0 };
	note->txt = TTF_RenderText_Solid(note->font, SDL_itoa(note->score, str, 10), color);
	SDL_Rect nbr = note->txt->clip_rect;
	nbr.x = 400;
	SDL_BlitSurface(note->txt ,NULL, note->win_srfc, &nbr);
	if (note->hp <= 0) {
 		note->game_over = TTF_RenderText_Solid(note->font, "Oops\nTry again", color);
 		nbr.x = 400;
 		nbr.y = 300;
 		SDL_BlitSurface(note->wlpp ,NULL, note->win_srfc, NULL);
 		SDL_BlitSurface(note->game_over ,NULL, note->win_srfc, &nbr);  
	}
}
