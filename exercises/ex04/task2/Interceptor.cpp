//
// Created by lena on 11/24/19.
//

#include "Interceptor.hpp"
#include "libFoo/foo.hpp"

#include <iostream>
#include <limits>
#include <random>
#include <dlfcn.h>

namespace foo {
    // declare a function pointer to simulate the call to foo in libFoo
    void (*another_print)();

    int random_number() {
        return 4; // improved determinism ;)
    }

    void just_a_print() {
        std::cout << "Your ad could be printed here!" << std::endl;

        // create a symbol for the function call
        void* symbol = dlsym(RTLD_NEXT, "_ZN3foo12just_a_printEv");
        // add the symbol to the function pointer
        another_print = (void (*)())symbol;
        // simulate function call
        another_print();
        std::cout << "Your ad space ends here!" << std::endl;
    }
}