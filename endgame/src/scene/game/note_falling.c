#include <hero.h>
#include "header.h"

int init_random(int low, int high) {
    int range = high - low;
    return (int) ((rand() / (float) (RAND_MAX)) * range) + low;
}


SDL_Rect set_coordinate(SDL_Rect rct, int speed) {
    // если больше 518у то начни с начала, двигайся со скоростю 4
    rct.y = (rct.y + rct.h >= 518) ? 0 : rct.y + speed;
    if (rct.y == 0)
        rct.x = init_random(0, 750);
    return (rct);
}

bool intersect(SDL_Rect rect1, SDL_Rect rect2) {
    bool x = 0;
    bool y = 0;

    if (rect1.x <= rect2.x && rect1.x + rect1.w >= rect2.x)
        x = 1;
    if (rect1.x >= rect2.x && rect1.x + rect1.w <= rect2.x + rect2.w)
        x = 1;
    if (rect1.x <= rect2.x + rect2.w && rect1.x + rect1.w >= rect2.x + rect2.w)
        x = 1;
    if (rect1.y <= rect2.y && rect1.y + rect1.h >= rect2.y)
        y = 1;
    if (rect1.y >= rect2.y && rect1.y + rect1.h <= rect2.y + rect2.h)
        y = 1;
    if (rect1.y <= rect2.y + rect2.h && rect1.y + rect1.h >= rect2.y + rect2.h)
        y = 1;

    return x == 1 && y == 1;
}

void note_falling(t_notes *note) {

    note->nota.n_1 = set_coordinate(note->nota.n_1, 4);
    note->nenota.n_1 = set_coordinate(note->nenota.n_1, 4);

    note->nota.n_2 = set_coordinate(note->nota.n_2, 6);
    note->nenota.n_2 = set_coordinate(note->nenota.n_2, 6);

    note->nota.n_3 = set_coordinate(note->nota.n_3, 8);
    note->nenota.n_3 = set_coordinate(note->nenota.n_3, 8);
}
