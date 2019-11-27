//
// Created by lena on 11/27/19.
//

#include <iostream>

#include "plugin.hpp"

class Foo : public Plugin {
public:
    void run() {
        std::cout << "running Foo plugin" << std::endl;
    }
    ~Bar() {
        std::cout << "deconstructing Foo plugin" << std::endl;
    }

    extern "C" std::unique_ptr<Plugin> createPlugin() {
        std::cout << "creating Foo plugin" << std::endl;
        return std::make_unique(Foo);
    }
};