#include "header.h"

void load_music(t_entity *player) {
    //Initialize SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    //Load audio files
    char path[1024];
    path_for_res("never-gonna-give-you-up.mp3", path);

    player->level_song = Mix_LoadMUS(path);
}
