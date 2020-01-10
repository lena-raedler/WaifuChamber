//
// Created by auki on 10.01.20.
//

#ifndef WAIFU_TRIANGLE_H
#define WAIFU_TRIANGLE_H


#include <algorithm>
#include "Vec2.h"

class triangle {
public:
    triangle() = default;
    triangle(const triangle&) = default;
    triangle(triangle&&) = default;
    triangle& operator=(const triangle&) & = default;
    triangle& operator=(triangle&&) & = default;

    triangle(vec_t a, vec_t b, vec_t c){
        points[0] = a;
        points[1] = b;
        points[2] = c;
    }

    vec_t points[3];
    vec_t a = points[0];
    vec_t b = points[1];
    vec_t c = points[2];

    vec_t operator[] (int id) const{
        std::clamp(id, 0, 2);
        return points[id];
    }
    vec_t& operator[](int id){
        std::clamp(id, 0, 2);
        return points[id];
    }

};


#endif //WAIFU_TRIANGLE_H
