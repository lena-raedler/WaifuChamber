//
// Created by bnorb on 13.11.19.
//

#include "main.hpp"
#include "unique_ptr_to_vec2.hpp"

int main() {
    unique_ptr_to_vec2 ptrToVec2 = unique_ptr_to_vec2(0, 0);
    ptrToVec2.print();

    ptrToVec2.setX(1);
    ptrToVec2.setY(2);
    ptrToVec2.print();

    ptrToVec2.set(7, 7);
    ptrToVec2.print();
}