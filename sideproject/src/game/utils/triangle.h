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
    triangle(const triangle& t) {
        points[0] = t.points[0];
        points[1] = t.points[1];
        points[2] = t.points[2];
    }
    triangle(triangle&& t){
        points[0] = t.points[0];
        points[1] = t.points[1];
        points[2] = t.points[2];
    }
    triangle& operator=(const triangle& t) &{
        points[0] = t.points[0];
        points[1] = t.points[1];
        points[2] = t.points[2];
        return *this;
    }
    triangle& operator=(triangle&& t) &{
        points[0] = t.points[0];
        points[1] = t.points[1];
        points[2] = t.points[2];
        return *this;
    }

    triangle(vec_t a, vec_t b, vec_t c){
        points[0] = a;
        points[1] = b;
        points[2] = c;
    }

    vec_t points[3];
    vec_t& a = points[0];
    vec_t& b = points[1];
    vec_t& c = points[2];

    vec_t operator[] (int id) const{
        std::clamp(id, 0, 2);
        return points[id];
    }
    vec_t& operator[](int id){
        std::clamp(id, 0, 2);
        return points[id];
    }

    vec_t max(){
        double x = std::numeric_limits<double>::min();
        double y = std::numeric_limits<double>::min();
        x = std::max(points[0].x, points[1].x);
        x = std::max(x, points[2].x);
        y = std::max(points[0].y, points[1].y);
        y = std::max(y, points[2].y);
        return {x, y};
    }
    vec_t min(){
        double x = std::numeric_limits<double>::max();
        double y = std::numeric_limits<double>::max();
        x = std::min(points[0].x, points[1].x);
        x = std::min(x, points[2].x);
        y = std::min(points[0].y, points[1].y);
        y = std::min(y, points[2].y);
        return {x, y};
    }

};


#endif //WAIFU_TRIANGLE_H
