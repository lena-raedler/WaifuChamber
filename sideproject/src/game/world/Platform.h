//
// Created by auki on 24.01.20.
//

#ifndef WAIFU_PLATFORM_H
#define WAIFU_PLATFORM_H
#include "../utils/Vec2.h"
#include "../GlobalConstants.h"
#include "../utils/triangle.h"
#include "../utils/utility.h"
#include <vector>
#include <utility>

class Movable;
enum platformType{PLATFORM = 0, WALL = 1, CEILING = 2, FLOOR = 3, SEMISOLID = 4};
class Platform {
public:
    Platform() = default;
    Platform(Platform& p) = default;
    Platform(Platform&& p) = default;
    Platform(std::pair<int,int> p, int typearg);

    std::pair<bool, bool> direction(Movable& m);
    triangle top;
    triangle bot;
    platformType type;
    bool collide(triangle& t);
};


#endif //WAIFU_PLATFORM_H
