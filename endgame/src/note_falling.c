//
// Created by User on 03.05.2020.
//
#include "../inc/header.h"

void note_falling(t_entity *note, int *level, int *score) {
    if (note->rect->y > WINDOW_HEIGHT) {
        note->rect->y = 0;
        note->rect->x = rand() % WINDOW_WIDTH;
        (*score)++;
        if (*score >= 10 * *level)
            *level += 1;
    }
    note->rect->y += 3 + *level;
}
