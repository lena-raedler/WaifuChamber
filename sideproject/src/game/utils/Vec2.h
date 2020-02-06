//
// Created by auki on 22.11.19.
//

#include <cmath>
#include <iostream>

#ifndef WAIFU_VEC2_H
#define WAIFU_VEC2_H

using value_t = double;

template<typename T>
struct Vec2 {
    T x = 0;
    T y = 0;





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
    Vec2 operator+(const Vec2& rhs) const { return {x + rhs.x, y + rhs.y}; }
    Vec2 operator*(const T& scalar) const { return {x * scalar, y * scalar}; }
    Vec2 operator/(const T& scalar) const { return {x / scalar, y / scalar}; }
    bool operator==(const Vec2& rhs) const { return (x == rhs.x && y == rhs.y); }
    void operator=(const Vec2& rhs) {
        x = rhs.x;
        y = rhs.y;
    }
    friend std::ostream& operator <<(std::ostream& os, const Vec2 vec2){
        os << "( " << vec2.x << ", " << vec2.y << " )";
        return os;
    }
    value_t length() const{
        return std::sqrt(x*x + y*y);
    }
    value_t sum() const{
        return x +y;
    }
    value_t dot(const Vec2& other) const{
        return x*other.x + y*other.y;
    }
    
    void max(const Vec2& other){
        if(x < other.x){
            x = other.x;
        }
        if(y < other.y){
            y = other.y;
        }
    }
    void min(const Vec2& other){
        if(x > other.x){
            x = other.x;
        }
        if(y > other.y){
            y = other.y;
        }
    }
    void normalize(){
        double div = std::sqrt(x*x + y*y);
        x /= div;
        y /= div;
    }
};
using vec_t = Vec2<value_t>;



#endif //WAIFU_VEC2_H
