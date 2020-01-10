//
// Created by auki on 06.12.19.
//
#include "utility.h"

namespace utility {
    std::vector <value_t> getBarycentricCoordinates(const triangle a,const vec_t b) {
        vec_t v0 = a[1] - a[0];
        vec_t v1 = a[2] - a[0];
        vec_t v2 = b - a[0];
        value_t cramer[5];
        cramer[0] = v0.dot(v0);
        cramer[1] = v0.dot(v1);
        cramer[2] = v1.dot(v1);
        cramer[3] = v2.dot(v0);
        cramer[4] = v2.dot(v1);
        value_t denom = cramer[0] * cramer[2] - cramer[1] * cramer[1];
        double u, v;
        u = (cramer[2] * cramer[3] - cramer[1] * cramer[4]) / denom;
        v = (cramer[0] * cramer[4] - cramer[1] * cramer[3]) / denom;
        return {u, v, 1 - u - v};

    }

    bool pointTriangleIntersection(const triangle a,const vec_t b) {
        auto bary = getBarycentricCoordinates(a, b);
        for (auto d : bary) {
            if (d > 1 || d < 0) {
                return false;
            }
        }
        return true;

    }

    bool lineLineIntersection(const vec_t aStart,const vec_t aEnd,const vec_t bStart,const vec_t bEnd){
        value_t tmp = (aStart.x - aEnd.x)*(bStart.y - bEnd.y) - (aStart.y - aEnd.y)*(bStart.x - bEnd.x);
        if (std::abs(tmp) <= std::numeric_limits<value_t>::epsilon()){
            std::cout << "mungojunge" << std::endl;
            return false;//parallel
        }
        value_t t,u;
        t = ((aStart.x - bStart.x)*(bStart.y - bEnd.y)-(aStart.y - bStart.y)*(bStart.x - bEnd.x))/tmp;
        u = ((aStart.x - aEnd.x)*(aStart.y - bStart.y)-(aStart.y - aEnd.y)*(aStart.x - bStart.x))/tmp;
        u *= -1; //not sure if this works
        std::cout << "t:" << t << " u:" << u << std::endl;
        return(t <= 1 && t >= 0 && u <= 1 && u >= 0);
    }
    bool triangleTriangleIntersection(const triangle a, const vec_t offseta, const triangle b, const vec_t offsetb){
        triangle a2 {a[0]+offseta, a[1] + offseta, a[2] + offseta};
        triangle b2 {b[0]+offsetb, b[1] + offsetb, b[2] + offsetb};
        return triangleTriangleIntersection(a2, b2);
    }

    bool triangleTriangleIntersection(const triangle a, const triangle b) {
        for (int i = 0; i < 3; ++i) {
            if (pointTriangleIntersection(a, b[i]) || pointTriangleIntersection(b, a[i])) {
                return true;
            }
        }
        return lineLineIntersection(a[0], a[1], b[0], b[1]) ||
               lineLineIntersection(a[1], a[2], b[0], b[1]) ||
               lineLineIntersection(a[0], a[2], b[0], b[1]) ||
               lineLineIntersection(a[0], a[1], b[1], b[2]) ||
               lineLineIntersection(a[1], a[2], b[1], b[2]) ||
               lineLineIntersection(a[0], a[2], b[1], b[2]) ||
               lineLineIntersection(a[0], a[1], b[0], b[2]) ||
               lineLineIntersection(a[1], a[2], b[0], b[2]) ||
               lineLineIntersection(a[0], a[2], b[0], b[2]);

    }
}