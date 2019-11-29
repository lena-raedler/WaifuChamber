//
// Created by lena on 11/27/19.
//

#include <iostream>
#include "plugin.hpp"

class Bar : public Plugin {
public:
    void run() {
        std::cout << "running Bar plugin" << std::endl;
    }

    ~Bar() {
        std::cout << "deconstructing Bar plugin" << std::endl;
    }
};

extern "C" {
    std::unique_ptr<Plugin> create_plugin() {
        std::cout << "creating Bar plugin" << std::endl;
        return std::make_unique<Bar>();
    }
}