//
// Created by auki on 24.01.20.
//

#ifndef WAIFU_GLOBALOBJECTS_H
#define WAIFU_GLOBALOBJECTS_H

#include <vector>
#include <memory>
class Player;
class Enemy;
class Gate;
class Projectile;
class Boss;
namespace GlobalObjects {
    extern std::vector<Enemy> enemies;
    extern std::vector<Platform> platforms;
    extern Player* playerPtr;//careful with that
    extern std::vector<Projectile> projectiles;
    extern std::vector<Gate> gates;
    extern std::pair<int, int> resolution;
    extern std::vector<Boss> bosses;
};


#endif //WAIFU_GLOBALOBJECTS_H
