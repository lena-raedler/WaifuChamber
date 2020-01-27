//
// Created by auki on 24.01.20.
//

#ifndef WAIFU_GLOBALOBJECTS_H
#define WAIFU_GLOBALOBJECTS_H

#include <vector>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
class Player;
class Enemy;
class Gate;
class Projectile;
class Boss;
struct SavedVariables;
namespace GlobalObjects {
    extern Mix_Chunk* chunkPtr[3];
    extern SavedVariables savedVariables;
    extern std::vector<Enemy> enemies;
    extern std::vector<Platform> platforms;
    extern Player* playerPtr;//careful with that
    extern std::vector<Projectile> projectiles;
    extern std::vector<Gate> gates;
    extern std::pair<int, int> resolution;
    extern std::vector<Boss> bosses;
};


#endif //WAIFU_GLOBALOBJECTS_H
