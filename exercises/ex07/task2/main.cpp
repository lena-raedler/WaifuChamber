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

    //std::cout << vec[1] << std::endl;
    auto res = (vec1 + vec2);
    std::cout << res.to_string() << std::endl;

    vec1[1] = 6.0;
    std::cout << vec1.to_string() << std::endl;

    std::cout << "testing Vec<1>" << std::endl;
    Vector<1> test{1.0};
    std::cout << test.to_string() << std::endl;
    std::cout << test.x << std::endl;
    std::cout << test[0] << std::endl;

    test.x = 21.0;
    std::cout << test.to_string() << std::endl;
    test[0] = 4.0;
    std::cout << test.to_string() << std::endl;

    std::cout << "testing Vec<2>" << std::endl;
    Vector<2> dim2{1.0, 2.0};
    std::cout << dim2.to_string() << std::endl;
    std::cout << dim2.x << std::endl;
    std::cout << dim2.y << std::endl;
    std::cout << dim2[1] << std::endl;

    dim2.x = 3.0;
    dim2.y = 4.5;
    std::cout << dim2.to_string() << std::endl;
    Vector<2> vec4{5.0, 2.0};
    std::cout << (vec4 + dim2).y << std::endl;

}