//
// Created by bnorb on 13.11.19.
//

#include "main.hpp"
#include "unique_ptr_to_vec2.hpp"
#include "shared_ptr_to_vec2.hpp"
#include <iostream>

void showUniquePtr();
void showSharedPtr();
void printSeparatorLine();


int main() {
    std::cout << "_.-~*° Show unique_ptr_to_vec2 °*~-._" << std::endl;
    //showUniquePtr();

    std::cout << "\n##################################################################\n\n";

    std::cout << "_.-~*° Show shared_ptr_to_vec2 °*~-._" << std::endl;
    showSharedPtr();
}

void showUniquePtr() {
    {   // Default constructor
        std::cout << "Use default constructor" << std::endl;
        unique_ptr_to_vec2 ptrToVec2;

        // Moving(?), the move constructor does not get printed though :thinking:
        unique_ptr_to_vec2 ptrToVec21 = unique_ptr_to_vec2();
    }

    printSeparatorLine();

    {
        std::cout << "Use move constructor" << std::endl;
        unique_ptr_to_vec2 ptrToVec2;
        unique_ptr_to_vec2 ptrToVec21(std::move(ptrToVec2));

        // Use move assignment (still buggy)
        unique_ptr_to_vec2 ptrToVec22;
        unique_ptr_to_vec2 ptrToVec23 = std::move(ptrToVec22);
    }

    printSeparatorLine();

    {   // Does not work, we are not allowed to copy!
        //unique_ptr_to_vec2 ptrToVec21 = ptrToVec2;
    }

    {
        std::cout << "Access unique_ptr_to_vec2 via *" << std::endl;
        unique_ptr_to_vec2 ptrToVec2;
        std::cout << "(*unique_ptr_to_vec2).x = " << (*ptrToVec2).x << std::endl;
        std::cout << "(*unique_ptr_to_vec2).y = " << (*ptrToVec2).y << std::endl;

        std::cout << "\nChange values to x = 1, y = 2" << std::endl;
        (*ptrToVec2).x = 1;
        (*ptrToVec2).y = 2;
        std::cout << "(*unique_ptr_to_vec2).x = " << (*ptrToVec2).x << std::endl;
        std::cout << "(*unique_ptr_to_vec2).y = " << (*ptrToVec2).y << std::endl;
    }

    printSeparatorLine();

    {
        std::cout << "Access unique_ptr_to_vec2 via ->" << std::endl;
        unique_ptr_to_vec2 ptrToVec2;
        std::cout << "unique_ptr_to_vec2->x = " << ptrToVec2->x << std::endl;
        std::cout << "unique_ptr_to_vec2->y = " << ptrToVec2->y << std::endl;

        std::cout << "\nChange values to x = 5, y = 4" << std::endl;
        ptrToVec2->x = 5;
        ptrToVec2->y = 4;
        std::cout << "unique_ptr_to_vec2->x = " << ptrToVec2->x << std::endl;
        std::cout << "unique_ptr_to_vec2->y = " << ptrToVec2->y << std::endl;
    }
}

void showSharedPtr() {
    {   // Default constructor
        std::cout << "Use default constructor" << std::endl;
        shared_ptr_to_vec2 ptrToVec2;

        // Moving(?), the move constructor does not get printed though :thinking:
        //unique_ptr_to_vec2 ptrToVec21 = unique_ptr_to_vec2();
    }

    printSeparatorLine();

    {
        std::cout << "Use copy constructor" << std::endl;
        shared_ptr_to_vec2 ptrToVec2;
        shared_ptr_to_vec2 ptrToVec21 = ptrToVec2;
    }

    printSeparatorLine();

    {
        std::cout << "Use move constructor" << std::endl;
        shared_ptr_to_vec2 ptrToVec2;
        shared_ptr_to_vec2 ptrToVec21 = std::move(ptrToVec2);
    }
}

void printSeparatorLine() {
    std::cout << "\n-----------------------------------\n\n";
}