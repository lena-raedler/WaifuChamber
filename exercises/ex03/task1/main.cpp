//
// Created by bnorb on 13.11.19.
//

#include "main.hpp"
#include "unique_ptr_to_vec2.hpp"
#include <iostream>
#include <memory>

int main() {

    {   // Default constructor
        unique_ptr_to_vec2 ptrToVec2;
    }
    std::cout << "hi" << std::endl;

    {   // Does not work, we are not allowed to copy!
        //unique_ptr_to_vec2 ptrToVec21 = ptrToVec2;
    }


    {
        unique_ptr_to_vec2 ptrToVec2;
        std::cout << "(*unique_ptr_to_vec2).x = " << (*ptrToVec2)->x << std::endl;
        std::cout << "(*unique_ptr_to_vec2).y = " << (*ptrToVec2)->y << std::endl;
    }
}