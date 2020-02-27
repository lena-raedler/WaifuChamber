//
// Created by auki on 13.02.20.
//
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <string>
#include <vector>
#include "../GlobalObjects.h"

#ifndef WAIFU_MUSICPLAYER_HPP
#define WAIFU_MUSICPLAYER_HPP
enum MusicType{AREAS, OTHER, BOSS};
class Song{
public:
    Mix_Music* music = NULL;
    std::string name;
    int start = 0;
    void free();
};
class MusicPlayer {


public:
    ~MusicPlayer();
    std::vector<Song> areas;
    std::vector<Song> other;
    std::vector<Song> bossThemes;

    MusicType musicType;
    size_t id;

    MusicType initialType;
    size_t initialId;
    bool paused = false;

    void togglePause();

    void load(MusicType m, std::string s);
    void play(MusicType m, std::string s);
    void play(MusicType m, size_t i);
    void play(MusicType m, std::string s, int loop);
    void play(MusicType m, size_t i, int loop);

    void load(MusicType m, std::string s, int st);

    void playInitial();
};


#endif //WAIFU_MUSICPLAYER_HPP
