//
// Created by auki on 06.12.19.
//

#ifndef WAIFU_UTILITY_H
#define WAIFU_UTILITY_H
#include "Vec2.h"
#include <vector>
using triangle = vec_t[3];
namespace utility {
    std::vector<value_t> getBarycentricCoordinates(const triangle a,const vec_t b);
    bool pointTriangleIntersection(const triangle a,const vec_t b);
    bool triangleTriangleIntersection(const triangle a,const triangle b);
    bool lineLineIntersection(const vec_t a1, const vec_t a2,const vec_t b1, const vec_t b2);
    int bongo();

}


#endif //WAIFU_UTILITY_H
