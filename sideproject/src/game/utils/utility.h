//
// Created by auki on 06.12.19.
//

#ifndef WAIFU_UTILITY_H
#define WAIFU_UTILITY_H
#include "Vec2.h"
#include <vector>
using triangle = vec_t[3];
namespace utility {
    std::vector<value_t> getBarycentricCoordinates(triangle a, vec_t b);
    bool pointTriangleIntersection(triangle a, vec_t b);
    bool triangleTriangleIntersection(triangle a, triangle b);

}


#endif //WAIFU_UTILITY_H
