//
// Created by auki on 06.12.19.
//
#include "utility.h"

namespace utility {
    std::vector <value_t> getBarycentricCoordinates(triangle a, vec_t b) {
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
        return {u, v, u - v};

    }

    bool pointTriangleIntersection(triangle a, vec_t b) {
        auto bary = getBarycentricCoordinates(a, b);
        for (auto d : bary) {
            if (d >= 1 || d <= 0) {
                return false;
            }
        }
        return true;

    }

    bool triangleTriangleIntersection(triangle a, triangle b) {
        for (int i = 0; i < 3; ++i) {
            if (pointTriangleIntersection(a, b[i])) {
                return true;
            }
        }
        return false;

    }
}