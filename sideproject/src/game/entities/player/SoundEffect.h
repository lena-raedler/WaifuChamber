//
// Created by auki on 11.02.20.
//
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <string>
#ifndef WAIFU_SOUNDEFFECT_H
#define WAIFU_SOUNDEFFECT_H
class SoundEffect{
public:
    Mix_Chunk* chunk = NULL;

    void play(){
        Mix_PlayChannel(-1, chunk, 0);
    }


    void load(std::string str, int volume){
        std::string s = "files/sounds/" + str;
        char* c = strcpy(new char[s.length() + 1], s.c_str());
        chunk = Mix_LoadWAV(c);
        Mix_VolumeChunk(chunk, volume);
    }
    void load(std::string str){
        load(str, 100);
    }
};
#endif //WAIFU_SOUNDEFFECT_H
