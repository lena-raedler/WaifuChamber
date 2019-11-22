//
// Created by auki on 22.11.19.
//

#include <cmath>

#ifndef WAIFU_VEC2_H
#define WAIFU_VEC2_H


template<typename T>
struct Vec2 {
    T x;
    T y;





    Vec2& operator+=(const Vec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vec2& operator-=(const Vec2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    Vec2& operator*=(const T& scalar)
    {
        x *= scalar;
        y *= scalar;

        return *this;
    }
    Vec2& operator/=(const T& scalar)
    {
        x /= scalar;
        y /= scalar;

        return *this;
    }
    Vec2 operator-(const Vec2& rhs) const { return {x - rhs.x, y - rhs.y}; }
    Vec2 operator*(const T& scalar) const { return {x * scalar, y * scalar}; }
    Vec2 operator/(const T& scalar) const { return {x / scalar, y / scalar}; }
    bool operator==(const Vec2& rhs) const { return (x == rhs.x && y == rhs.y); }
    double distance(){
        return std::sqrt(x*x + y*y);
    }
};
using value_t = double;
using vec_t = Vec2<value_t>;

#endif //WAIFU_VEC2_H
