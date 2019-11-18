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

//unique_ptr_to_vec2::unique_ptr_to_vec2(const unique_ptr_to_vec2&) = delete;

unique_ptr_to_vec2::~unique_ptr_to_vec2() {
    delete(vec2);
    std::cout << "Vec2#" << this << " destroyed" << std::endl;
}

Vec2& unique_ptr_to_vec2::operator*() {
    return *vec2;
}