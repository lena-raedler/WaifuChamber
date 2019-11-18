//
// Created by bnorb on 18.11.19.
//

#include "ReferenceCounter.hpp"
#include <iostream>

ReferenceCounter::ReferenceCounter() {
    count = 0;
    std::cout << "ReferenceCounter#" << this << " constructed" << std::endl;
}
