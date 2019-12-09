
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
        std::cout << "Testing copy constructor" << std::endl;
        MyVector<int, 5> vec1;
        MyVector<int, 5> vec2(vec1);
    }

    {
        std::cout << "Testing copy assignment" << std::endl;
        MyVector<int, 5> vec1;
        MyVector<int, 5> vec2;
        vec2 = vec1;
    }

    {
        //std::cout << "Testing move assignment" << std::endl;
        //MyVector<int, 5> vec1;
        //MyVector<int, 5> vec2 = std::move(vec1);
    }
}