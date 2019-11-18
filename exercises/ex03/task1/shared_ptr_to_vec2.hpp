//
// Created by bnorb on 18.11.19.
//

#ifndef APP_SHARED_PTR_TO_VEC2_HPP
#define APP_SHARED_PTR_TO_VEC2_HPP

#include "Vec2.hpp"
#include "ReferenceCounter.hpp"

class shared_ptr_to_vec2 {

public:
    shared_ptr_to_vec2();
    shared_ptr_to_vec2(const shared_ptr_to_vec2 &from);
    shared_ptr_to_vec2(shared_ptr_to_vec2 &&from);
    ~shared_ptr_to_vec2();

private:
    Vec2* vec2;
    ReferenceCounter* referenceCounter;
};


#endif //APP_SHARED_PTR_TO_VEC2_HPP
