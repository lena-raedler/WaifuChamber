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

shared_ptr_to_vec2::shared_ptr_to_vec2(shared_ptr_to_vec2 &&from) {
    std::cout << "Move construct shared_ptr_to_vec2" << std::endl;
    vec2 = from.vec2;
    referenceCounter = from.referenceCounter;

    from.vec2 = nullptr;
    from.referenceCounter = nullptr;
}

shared_ptr_to_vec2::~shared_ptr_to_vec2() {
    // vec2 == nullptr is an indication that that instance has been moved!
    if (referenceCounter && --(referenceCounter->count) <= 0 && vec2) {
        delete referenceCounter;
        delete vec2;
    }
    std::cout << "shared_ptr_to_vec2#" << this << " destroyed" << std::endl;
}

shared_ptr_to_vec2 &shared_ptr_to_vec2::operator=(const shared_ptr_to_vec2 &from) {
    if (&from == this) {
        return *this;
    }

    std::cout << "Copy assign shared_ptr_to_vec2" << std::endl;
    vec2 = from.vec2;
    referenceCounter = from.referenceCounter;
    referenceCounter->count++;
    return *this;
}

shared_ptr_to_vec2 &shared_ptr_to_vec2::operator=(shared_ptr_to_vec2 &&from) {
    // Assigning a shared_ptr_to_vec2 to itself should do nothing.
    if (&from == this) {
        return *this;
    }

    std::cout << "Move shared_ptr_to_vec2" << std::endl;
    vec2 = from.vec2;
    referenceCounter = from.referenceCounter;
    from.vec2 = nullptr;
    from.referenceCounter = nullptr;

    return *this;
}


Vec2& shared_ptr_to_vec2::operator*() {
    return *vec2;
}

Vec2* shared_ptr_to_vec2::operator->() {
    return vec2;
}