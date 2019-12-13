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

    Vector<4> vec2 = vec1;
    std::cout << vec2.to_string() << std::endl;

    Vector<1> vec3(std::move(vec));
    std::cout << vec3.to_string() << std::endl;

    std::cout << vec[1] << std::endl;
    auto res = vec1 + vec2;
    std::cout << res.to_string() << std::endl;

    vec1[1] = 6.0;
    std::cout << vec1.to_string() << std::endl;

}