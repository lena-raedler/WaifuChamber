//
// Created by bnorb on 18.11.19.
//

#include "shared_ptr_to_vec2.hpp"
#include "ReferenceCounter.hpp"
#include <iostream>

shared_ptr_to_vec2::shared_ptr_to_vec2() {
    referenceCounter = new ReferenceCounter;
    referenceCounter->count = 1;

    vec2 = new Vec2;
    vec2->x = 0;
    vec2->y = 0;

    std::cout << "shared_ptr_to_vec2#" << this << " constructed" << std::endl;
}


shared_ptr_to_vec2::shared_ptr_to_vec2(const shared_ptr_to_vec2 &from) {
    std::cout << "Copy construct shared_ptr_to_vec2" << std::endl;
    vec2 = from.vec2;
    referenceCounter = from.referenceCounter;
    referenceCounter->count++;
}


shared_ptr_to_vec2::~shared_ptr_to_vec2() {
    referenceCounter->count--;
    if (referenceCounter->count <= 0) {
        delete referenceCounter;
        delete vec2;
    }
    std::cout << "shared_ptr_to_vec2#" << this << " destroyed" << std::endl;
}