//
// Created by bnorb on 08.12.19.
//

#include <iostream>
#include "MyVector.cpp"

int main () {
    std::cout << "Creating an int vector" << std::endl;
    MyVector<int, 5> vec();

    std::cout << "Creating a double vector" << std::endl;
    MyVector<double, 5> vec2();
}