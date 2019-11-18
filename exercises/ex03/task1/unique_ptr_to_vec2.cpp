//
// Created by bnorb on 13.11.19.
//

#include "unique_ptr_to_vec2.hpp"
#include <iostream>

unique_ptr_to_vec2::unique_ptr_to_vec2() {
    vec2 = new Vec2;
    vec2->x = 0;
    vec2->y = 0;
    std::cout << "Vec2#" << this << " constructed" << std::endl;
}

unique_ptr_to_vec2::unique_ptr_to_vec2(unique_ptr_to_vec2&& from) {
    std::cout << "Moving unique_ptr_to_vec2 with constructor" << std::endl;
    vec2 = from.vec2;
    from.vec2 = nullptr;
}

unique_ptr_to_vec2::~unique_ptr_to_vec2() {
    delete(vec2);
    std::cout << "Vec2#" << this << " destroyed" << std::endl;
}

unique_ptr_to_vec2 &unique_ptr_to_vec2::operator=(unique_ptr_to_vec2 &&from) {
    std::cout << "Moving unique_ptr_to_vec2 with operator" << std::endl;
    vec2 = from.vec2;
    from.vec2 = nullptr;
    return *this;
}

Vec2& unique_ptr_to_vec2::operator*() {
    return *vec2;
}

Vec2* unique_ptr_to_vec2::operator->() {
    return vec2;
}