//
// Created by bnorb on 13.11.19.
//

#ifndef APP_UNIQUE_PTR_TO_VEC2_HPP
#define APP_UNIQUE_PTR_TO_VEC2_HPP

#include "Vec2.hpp"

class unique_ptr_to_vec2 {

public:
    unique_ptr_to_vec2();

    // Copy constructor and assignment should not be possible for unique_ptr
    unique_ptr_to_vec2(const unique_ptr_to_vec2 &) = delete;
    unique_ptr_to_vec2& operator=(const unique_ptr_to_vec2& ) = delete;

    // Move constructor and assignment
    unique_ptr_to_vec2(unique_ptr_to_vec2 &&from);
    unique_ptr_to_vec2& operator=(unique_ptr_to_vec2 &&from);

    ~unique_ptr_to_vec2();

    Vec2& operator*();
    Vec2* operator->();

private:
    Vec2* vec2;
};


#endif //APP_UNIQUE_PTR_TO_VEC2_HPP
