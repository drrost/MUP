#include "header.h"

void print_window(t_notes *note) {

	SDL_BlitSurface(note->wlpp ,NULL, note->win_srfc, NULL);// распечатай фон
	SDL_BlitSurface(note->player.srf, NULL, note->win_srfc, &note->player.n_1); // print player
	print_heart_score(note);
	if (note->hp > 0) {
		SDL_BlitSurface(note->nota.srf, NULL, note->win_srfc, &note->nota.n_1); // что куда где нота
		SDL_BlitSurface(note->nenota.srf, NULL, note->win_srfc, &note->nenota.n_1); // что куда где	не нота
		SDL_BlitSurface(note->nota.srf, NULL, note->win_srfc, &note->nota.n_2); // что куда где 2 ноты
		SDL_BlitSurface(note->nenota.srf, NULL, note->win_srfc, &note->nenota.n_2); // что куда где	2 не ноты
		SDL_BlitSurface(note->nota.srf, NULL, note->win_srfc, &note->nota.n_3); // что куда где 3 нота
		SDL_BlitSurface(note->nenota.srf, NULL, note->win_srfc, &note->nenota.n_3); // что куда где	3 не ноты
	}
	SDL_UpdateWindowSurface(note->window); // фото в рамку
}
