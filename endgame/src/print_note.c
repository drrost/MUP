#include "header.h"

void print_notes(App *app, t_notes *note) {
	if (note->hp > 0) {
		SDL_RenderCopy(app->renderer, note->nota.textr, NULL, &note->nota.n_1);
		SDL_RenderCopy(app->renderer, note->nenota.textr, NULL, &note->nenota.n_1);
		SDL_RenderCopy(app->renderer, note->nota.textr, NULL, &note->nota.n_2);
		SDL_RenderCopy(app->renderer, note->nenota.textr, NULL, &note->nenota.n_2);
		SDL_RenderCopy(app->renderer, note->nota.textr, NULL, &note->nota.n_3);
		SDL_RenderCopy(app->renderer, note->nenota.textr, NULL, &note->nenota.n_3);
	}
	// SDL_RenderPresent(app->renderer);
}
