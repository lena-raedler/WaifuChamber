//
// Created by lena on 11/27/19.
//


#include <iostream>
#include <memory>
#include <dlfcn.h>
#include <string>

#include "plugin.hpp"

void runPlugin(std::string path) {

    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if(!handle) { return;}
    std::unique_ptr<Plugin> (*create)();
    {
        create = (std::unique_ptr<Plugin> (*)()) dlsym(handle, "PLUGIN_CONSTRUCTOR");
        std::unique_ptr<Plugin> plugin = (std::unique_ptr<Plugin>) create();
        plugin->run();
    }
    dlclose(handle);
}

int main(int argc, char** argv) {
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;
    runPlugin(argv[1]);
    runPlugin(argv[2]);
    return 0;
}
