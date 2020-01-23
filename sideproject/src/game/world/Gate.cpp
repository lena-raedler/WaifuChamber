//
// Created by lena on 1/23/20.
//

#include "Gate.h"

Gate::Gate() {}
Gate::Gate(std::vector<std::pair<int, int>> position, std::string path) {
    position = position;
    nextRoomPath = path;

    std::cout << nextRoomPath << std::endl;
}

Gate::~Gate() {}
