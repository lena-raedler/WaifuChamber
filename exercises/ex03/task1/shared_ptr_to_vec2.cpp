//
// Created by bnorb on 18.11.19.
//

#include "shared_ptr_to_vec2.hpp"
#include <iostream>

shared_ptr_to_vec2::shared_ptr_to_vec2() {
    vec2 = new Vec2;
    vec2->x = 0;
    vec2->y = 0;
}

shared_ptr_to_vec2::~shared_ptr_to_vec2() {

}