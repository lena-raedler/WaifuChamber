//
// Created by lena on 11/23/19.
//

#include "Person.h"
#include <iostream>
#include <memory>
#include <string>



int main(int argc, char *argv[]) {
    Person p1{"Mohamed", "Lee",42};
    std::cout << p1 << std::endl;
    std::cout << "Done" << std::endl;
}