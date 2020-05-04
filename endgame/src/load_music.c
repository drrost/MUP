//
// Created by User on 04.05.2020.
//
#include "header.h"

void load_music(t_entity *player){
    //Initialize SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    //Load audio files
    char selected_song[] = "../resources/never-gonna-give-you-up.mp3";
    player->level_song = Mix_LoadMUS(selected_song);
}
