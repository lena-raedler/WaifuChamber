//
// Created by bnorb on 13.11.19.
//

#include "unique_ptr_to_vec2.hpp"
#include <iostream>
#include <memory>

unique_ptr_to_vec2::unique_ptr_to_vec2(int x, int y) {
    vec2.x = x;
    vec2.y = y;
}

unique_ptr_to_vec2::~unique_ptr_to_vec2() {

}

void unique_ptr_to_vec2::setX(int x) {
    vec2.x = x;
}

void unique_ptr_to_vec2::setY(int y) {
    vec2.y = y;
}

void unique_ptr_to_vec2::set(int x, int y) {
    vec2.x = x;
    vec2.y = y;
}

void unique_ptr_to_vec2::print() {
    std::cout << "x : " << vec2.x << std::endl;
    std::cout << "y : " << vec2.y << std::endl;
}