#include <hero.h>
#include "header.h"

int init_random(int low, int high) {
    int range = high - low;
    return (int) ((rand() / (float) (RAND_MAX)) * range) + low;
}


SDL_Rect set_coordinate(SDL_Rect rct, int speed) {
    // если больше 400у то начни с начала, двигайся со скоростю 1
    rct.y = (rct.y > 500) ? 0 : rct.y + speed;
    if (rct.y == 0)
        rct.x = init_random(0, 750);
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

// int hero_hp(t_notes *note, t_hero hero, int lives) {
//     int hp = lives;

//     if (compare(hero.rect, note->nenota.n_1)) {
// 		if (lives > 0 && (note->nenota.n_1.y = 456))
// 			hp--;
// 	}
// 	if (compare(hero.rect, note->nenota.n_2)) {
// 		if (lives > 0 && (note->nenota.n_2.y = 456))
// 			hp--;
// 	}
// 	if (compare(hero.rect, note->nenota.n_3))  {
// 		if (lives > 0 && (note->nenota.n_3.y = 456))
// 			hp--;
//     }
//     return hp;
// }

// int hero_score(t_notes *note, t_hero hero, int current_score) {
//     int ochko = current_score;

// 	if ((compare(hero.rect, note->nota.n_1)) == 1) {
// 		if ((note->nota.n_1.y = 456))
// 			ochko++;
// 	}
// 	if ((compare(hero.rect, note->nota.n_2)) == 1) {
// 		if ((note->nota.n_2.y = 456))
// 			ochko++;
// 	}
// 	if ((compare(hero.rect, note->nota.n_3)) == 1)  {
// 		if ((note->nota.n_3.y = 456))
// 			ochko++;
// 	}
//     return ochko;
// }



void note_falling(t_notes *note) {
    if (note->step == 1) {
        // is_catch_note(note);

        note->nota.n_1 = set_coordinate(note->nota.n_1, 2);
        note->nenota.n_1 = set_coordinate(note->nenota.n_1, 2);

        note->nota.n_2 = set_coordinate(note->nota.n_2, 4);
        note->nenota.n_2 = set_coordinate(note->nenota.n_2, 4);

        note->nota.n_3 = set_coordinate(note->nota.n_3, 6);
        note->nenota.n_3 = set_coordinate(note->nenota.n_3, 6);
    }
}
