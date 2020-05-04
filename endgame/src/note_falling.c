#include "header.h"

int init_random(int low, int high) {
	int range = high - low;
	return (int)((rand() / (float)(RAND_MAX)) * range) + low;
}

SDL_Rect set_coordinate(SDL_Rect rct, int speed) {
	rct.y = (rct.y > 600) ? 0 : rct.y + speed; // если больше 600у то начни с начала, двигайся со скоростю 1 - блу
	if (rct.y == 0)
		rct.x = init_random(0, 800);
	return (rct);
}

bool compare(SDL_Rect a, SDL_Rect b) {
	bool x = 0;
	bool y = 0;
	if (a.x <= b.x && a.x + a.w >= b.x)
		x = 1;
	if (a.x >= b.x && a.x + a.w <= b.x + b.w)
		x = 1;
	if (a.x <= b.x + b.w && a.x + a.w >= b.x + b.w)
		x = 1;
	if (a.y <= b.y && a.y + a.h >= b.y)
		y = 1;
	if (a.y >= b.y && a.y + a.h <= b.y + b.h)
		y = 1;
	if (a.y <= b.y + b.h && a.y + a.h >= b.y + b.h)
		y = 1;
	if (x == 1 && y == 1)
		return 1;
	return 0;
}

void is_catch_note(t_notes *note) {
	if ((compare(note->player.n_1, note->nenota.n_1)) == 1) {
		if (note->hp > 0 && (note->nenota.n_1.y = 400))
			note->hp--;
	}
	if ((compare(note->player.n_1, note->nenota.n_2)) == 1) {
		if (note->hp > 0 && (note->nenota.n_2.y = 400))
			note->hp--;
	}
	if ((compare(note->player.n_1, note->nenota.n_3)) == 1)  {
		if (note->hp > 0 && (note->nenota.n_3.y = 400))
			note->hp--;
	}

	if ((compare(note->player.n_1, note->nota.n_1)) == 1) {
		if ((note->nota.n_1.y = 400))
			note->score += 63;
	}
	if ((compare(note->player.n_1, note->nota.n_2)) == 1) {
		if ((note->nota.n_2.y = 400))
			note->score += 63;
	}
	if ((compare(note->player.n_1, note->nota.n_3)) == 1)  {
		if ((note->nota.n_3.y = 400))
			note->score += 63;
	}

}

void note_falling(t_notes *note, int x) {
	if (x > (note->w - 64))
		x = note->w - 64;
	if (x < 64)
		x = 64;
	note->player.n_1.x = x - 64; // центрирование картиночки с мышкой

	if (note->step == 1) {
		is_catch_note(note);

		note->nota.n_1 = set_coordinate(note->nota.n_1, 1);
		note->nenota.n_1 = set_coordinate(note->nenota.n_1, 2);

		note->nota.n_2 = set_coordinate(note->nota.n_2, 3);
		note->nenota.n_2 = set_coordinate(note->nenota.n_2, 4);

		note->nota.n_3 = set_coordinate(note->nota.n_3, 5);
		note->nenota.n_3 = set_coordinate(note->nenota.n_3, 6);
	}
}
