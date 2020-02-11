//
// Created by auki on 24.01.20.
//
#ifndef WAIFU_GLOBALCONSTANTS_H
#define WAIFU_GLOBALCONSTANTS_H
#include <vector>
#include "./utils/Rgba.hpp"

namespace GlobalConstants {
    constexpr int deltaDenom = 100;
    constexpr int tileSize = 32;
    constexpr double epsilon = 0.001;

    // Colors
    constexpr Rgba WHITE  = { 0xFF, 0xFF, 0xFF, 0xFF };
    constexpr Rgba YELLOW = { 0xFF, 0xCC, 0x00, 0xFF };
    constexpr Rgba BLUE = { 0x00, 0x00, 0xFF, 0xFF };
    constexpr Rgba ORANGE = { 0xFF, 0x88, 0x00, 0xFF };
    constexpr Rgba BROWN = { 0x88, 0x44, 0xFF, 0xFF};
};


#endif //WAIFU_GLOBALCONSTANTS_H
