//
// Created by auki on 24.01.20.
//

#ifndef WAIFU_PLATFORM_H
#define WAIFU_PLATFORM_H
#include "../utils/Vec2.h"
#include "../GlobalConstants.h"
#include <vector>
#include <utility>

class Platform {
public:
    Platform() = default;
    Platform(Platform& p) = default;
    Platform(Platform&& p) = default;
    Platform(std::pair<int,int> p, bool semi);

    vec_t pos[4];//topleft, topright, botleft, botright
    bool semisolid;
};


#endif //WAIFU_PLATFORM_H
