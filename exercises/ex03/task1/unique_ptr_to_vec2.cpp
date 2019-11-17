//
// Created by bnorb on 13.11.19.
//

#include "unique_ptr_to_vec2.hpp"
#include <iostream>
#include <memory>
#include <vector>

/*
unique_ptr_to_vec2::unique_ptr_to_vec2(int x = 0, int y = 0) {
    vec2 = new Vec2; 
    vec2->x = x;
    vec2->y = y;
    //used = true;
}
 */

unique_ptr_to_vec2::unique_ptr_to_vec2(Vec2 vec2_arg = {0, 0}) {

    //if(used) {
    //    return;
    //}

    vec2 = new Vec2;
    vec2->x = vec2_arg.x;
    vec2->y = vec2_arg.y;
    used = true;
    //unique_ptr_to_vec2::used = true;
}

unique_ptr_to_vec2::~unique_ptr_to_vec2() {
    delete(vec2);
}






void unique_ptr_to_vec2::setX(int x) {
    vec2->x = x;
}

void unique_ptr_to_vec2::setY(int y) {
    vec2->y = y;
}

void unique_ptr_to_vec2::set(int x, int y) {
    vec2->x = x;
    vec2->y = y;
}

void unique_ptr_to_vec2::print() {
    std::cout << "x : " << vec2->x << std::endl;
    std::cout << "y : " << vec2->y << std::endl;
}