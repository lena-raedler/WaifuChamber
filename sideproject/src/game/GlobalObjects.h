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
class Checkpoint;
class Ability;
struct SavedVariables;
namespace GlobalObjects {
    extern Mix_Chunk* chunkPtr[3];
    extern SavedVariables savedVariables;
    extern std::vector<std::shared_ptr<Enemy>> enemies;
    extern std::vector<std::shared_ptr<Platform>> platforms;
    extern Player* playerPtr;//careful with that
    extern std::vector<std::shared_ptr<Projectile>> projectiles;
    extern std::vector<std::shared_ptr<Gate>> gates;
    extern std::pair<int, int> resolution;
    extern std::vector<std::shared_ptr<Boss>> bosses;
    extern std::vector<Checkpoint> checkpoints;
    extern std::vector<Ability> abilities; //0 ranged 1 melee
};


#endif //WAIFU_GLOBALOBJECTS_H
