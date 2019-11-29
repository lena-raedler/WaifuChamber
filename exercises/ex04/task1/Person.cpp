//
// Created by lena on 11/23/19.
//

#include "Person.h"
#include <iostream>
#include <memory>
#include <string>



int main(int argc, char *argv[]) {
    foo::Person p1{"Mohamed", "Lee", 42};
    foo::Person p2{"Mohamed", "Lee", 42};
    foo::Person p3{"John", "Smith", 3};
    foo::Person p4{"Mohammed", "Lee", 42};

    auto equal = p1 == p2;
    std::cout << equal << "\n\n" << std::endl;

    equal = p2 != p3;
    std::cout << equal << "\n\n" << std::endl;

    equal = p3 < p1;
    std::cout << equal << "\n\n" << std::endl;

    equal = p3 > p1;
    std::cout << equal << "\n\n" << std::endl;

    equal = p1 <= p2;
    std::cout << equal << "\n\n" << std::endl;

    equal = p2 <= p3;
    std::cout << equal << "\n\n" << std::endl;

    equal = p4 >= p2;
    std::cout << equal << "\n\n" << std::endl;

    equal = p3 >= p1;
    std::cout << equal << "\n\n" << std::endl;


    std::cout << p1 << std::endl;
    std::cout << "Done" << std::endl;
}