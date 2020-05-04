//
// Created by User on 04.05.2020.
//
#include "header.h"

void load_music(t_entity *player){
    //Initialize SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    //Load audio files
    char path[1024];

    int n = 3;
    char *tracks[] = {"mp3/doowit.mp3", "mp3/jj.mp3",
                      "mp3/never-gonna-give-you-up.mp3"};
    int i = rand() % n;
    path_for_res(tracks[i], path);

    player->level_song = Mix_LoadMUS(path);
}
