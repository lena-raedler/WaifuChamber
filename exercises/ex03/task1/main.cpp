//
// Created by bnorb on 13.11.19.
//

#include "main.hpp"
#include "unique_ptr_to_vec2.hpp"
#include <iostream>
#include <memory>

int main() {
    //std::unique_ptr<int> ptr = std::make_unique<int>();

    //unique_ptr_to_vec2 ptrToVec2 = unique_ptr_to_vec2();

    {   // Default constructor
        unique_ptr_to_vec2 ptrToVec2;
    }
    std::cout << "hi" << std::endl;

    {   // Does not work, we are not allowed to copy!
        //unique_ptr_to_vec2 ptrToVec21 = ptrToVec2;
    }

    //ptrToVec2.print();
    //ptrToVec2.print();

    /*
    ptrToVec2.setX(2);
    ptrToVec2.setY(3);
    ptrToVec2.print();

    ptrToVec2.set(7, 7);
    ptrToVec2.print();
     */
}