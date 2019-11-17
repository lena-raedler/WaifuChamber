//
// Created by bnorb on 13.11.19.
//

#include "main.hpp"
#include "unique_ptr_to_vec2.hpp"

int main() {
    Vec2 vec2 = {1, 1};
    unique_ptr_to_vec2 ptrToVec2 = unique_ptr_to_vec2(vec2);
    //unique_ptr_to_vec2 ptrToVec21 = ptrToVec2;
    ptrToVec2.print();

    ptrToVec2.setX(2);
    ptrToVec2.setY(3);
    ptrToVec2.print();

    ptrToVec2.set(7, 7);
    ptrToVec2.print();
}