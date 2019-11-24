//
// Created by lena on 11/24/19.
//

#include "Interceptor.hpp"
#include "libFoo/foo.hpp"

#include <iostream>
#include <limits>
#include <random>


namespace foo {

    int random_number() {
        return 4; // improved determinism ;)
    }

    void just_a_print() {
        std::cout << "Your ad could be printed here!" << std::endl;
        foo::just_a_print();
        std::cout << "Your ad space ends here!" << std::endl;
    }
}