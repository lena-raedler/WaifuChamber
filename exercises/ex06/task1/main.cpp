//
// Created by bnorb on 08.12.19.
//

#include <iostream>
#include "MyVector.cpp"

int main () {
    {
        std::cout << "Creating an int vector" << std::endl;
        MyVector<int, 5> vecInt;
    }

    {
        std::cout << "Creating a double vector" << std::endl;
        MyVector<double, 5> vecDouble;
    }

    {
        std::cout << "Creating a float vector" << std::endl;
        MyVector<float, 5> vecFloat;
    }

    {
        std::cout << "Testing copy- constructor and assignment" << std::endl;
        MyVector<int, 5> vec1;
        MyVector<int, 5> vec2(vec1);
    }
}