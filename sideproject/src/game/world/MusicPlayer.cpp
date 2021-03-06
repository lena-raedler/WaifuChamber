//
// Created by auki on 13.02.20.
//

#include "MusicPlayer.h"
#include "../SavedVariables.h"

void Song::free(){
    Mix_FreeMusic(music);
}
MusicPlayer::~MusicPlayer(){
    for(auto a : areas){
        a.free();
    }
    for(auto b : bossThemes){
        b.free();
    }
    for(auto c : other){
        c.free();
    }
}
void MusicPlayer::load(MusicType m, std::string s, int st) {
    std::string str = "files/music/" + s;
    char* c = strcpy(new char[str.length() + 1], str.c_str());
    switch(m){
        case AREAS:
            areas.push_back(Song());
            areas.back().music = Mix_LoadMUS(c);
            areas.back().start = st;
            areas.back().name = s;
            break;
        case OTHER:
            other.push_back(Song());
            other.back().music = Mix_LoadMUS(c);
            other.back().start = st;
            other.back().name = s;
            break;
        case BOSS:
            bossThemes.push_back(Song());
            bossThemes.back().music = Mix_LoadMUS(c);
            bossThemes.back().start = st;
            bossThemes.back().name = s;
            break;
    }
}
void MusicPlayer::load(MusicType m, std::string s) {
    load(m, s, 0);
}
void MusicPlayer::play(MusicType m, size_t i, int loop) {
    std::cout << "Now Playing: " << i << std::endl;

    Mix_VolumeMusic(GlobalObjects::savedVariables.musicVolume * 12);
    if(m == musicType && i == id && Mix_PlayingMusic()){
        return;
    }
    musicType = m;
    id = i;//to get which song is being played idk if useful
    switch(m){
        case AREAS:
            if(areas.size() > i) {
                Mix_PlayMusic(areas[i].music, loop);
            }
            break;
        case OTHER:
            if(other.size() > i) {
                Mix_PlayMusic(other[i].music, loop);
            }
            break;
        case BOSS:
            if(bossThemes.size() > i) {
                Mix_PlayMusic(bossThemes[i].music, loop);
            }
            break;
        default:
            break;

    }
}
void MusicPlayer::play(MusicType m, size_t i) {
    play(m, i, -1);
}

void MusicPlayer::togglePause(){
    if(!paused){
        Mix_PauseMusic();
    } else{
        Mix_ResumeMusic();
    }
    paused = !paused;
}
void MusicPlayer::playInitial(){
    switch(initialType){
        case AREAS:
            if(areas.size() > initialId) {
                Mix_PlayMusic(areas[initialId].music, -1);
            }
            break;
        case OTHER:
            if(other.size() > initialId) {
                Mix_PlayMusic(other[initialId].music, -1);
            }
            break;
        case BOSS:
            if(bossThemes.size() > initialId) {
                Mix_PlayMusic(bossThemes[initialId].music, -1);
            }
            break;
        default:
            break;

    }
}