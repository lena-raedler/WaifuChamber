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
#include "Image.h"
#include "../world/Gate.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/compare.hpp>
#include "../world/gateInformation.h"
#include "../world/LockedWall.h"
#include "../entities/player/EnemyInformation.h"

class Room;

namespace utility {
    bool hitboxCollision(std::vector<triangle> a, vec_t posA, std::vector<triangle> b, vec_t posB);
    vec_t convert(std::pair<int, int> p);
    std::vector<value_t> getBarycentricCoordinates(const triangle a,const vec_t b);
    bool pointTriangleIntersection(const triangle a,const vec_t b);
    bool triangleTriangleIntersection(const triangle a,const triangle b);
    bool triangleTriangleIntersection(const triangle a, const vec_t offseta, const triangle b, const vec_t offsetb);
    bool lineLineIntersection(const vec_t a1, const vec_t a2,const vec_t b1, const vec_t b2);
    void fillDefaultHitbox(std::vector<triangle>& vec, int i, vec_t offset);
    void fillDefaultHitbox(std::vector<triangle>& v);
    int bongo();
    Room parseRoom(std::string path, Renderer &renderer, std::pair<int, int> resolution);
    Image loadImage(std::string path, Renderer& renderer);
    void fillDefaultHitbox(std::vector<triangle>& vec, int i);
    vec_t getMax(std::vector<triangle>& tris);
    vec_t getMin(std::vector<triangle>& tris);

}


#endif //WAIFU_UTILITY_H
