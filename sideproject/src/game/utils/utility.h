//
// Created by auki on 06.12.19.
//

#ifndef WAIFU_UTILITY_H
#define WAIFU_UTILITY_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vec2.h"
#include "triangle.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <unordered_map>
#include "renderer.h"
#include "ImageNew.hpp"
#include "../world/Gate.h"

class Room;

namespace utility {
    std::vector<value_t> getBarycentricCoordinates(const triangle a,const vec_t b);
    bool pointTriangleIntersection(const triangle a,const vec_t b);
    bool triangleTriangleIntersection(const triangle a,const triangle b);
    bool triangleTriangleIntersection(const triangle a, const vec_t offseta, const triangle b, const vec_t offsetb);
    bool lineLineIntersection(const vec_t a1, const vec_t a2,const vec_t b1, const vec_t b2);
    int bongo();
    Room parseRoom(Room room, std::string path, Renderer &renderer, std::pair<int, int> resolution);
    ImageNew loadImage(std::string path, Renderer& renderer);
}


#endif //WAIFU_UTILITY_H
