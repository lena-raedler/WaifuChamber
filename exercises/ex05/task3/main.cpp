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
    if(!handle) { exit(-1);}
    std::unique_ptr<Plugin> (*create)();
    {
        create = (std::unique_ptr<Plugin> (*)()) dlsym(handle, "create_plugin");
        std::unique_ptr<Plugin> plugin = (std::unique_ptr<Plugin>) create();
        plugin->run();
    }
    dlclose(handle);
}

int main(int argc, char** argv) {
    runPlugin(argv[1]);
    runPlugin(argv[2]);
    return 0;
}
