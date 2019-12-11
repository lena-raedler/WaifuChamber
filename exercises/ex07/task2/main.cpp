//
// Created by lena on 12/11/19.
//

#include "vector.h"
#include <iostream>
#include <array>

int main() {
    Vector<1> vec;
    std::cout <<vec.to_string() << std::endl;

    Vector<4> vec1{1.0, 2.0, 3.0, 4.0};
    std::cout << vec1.to_string() << std::endl;
    return 0;
}