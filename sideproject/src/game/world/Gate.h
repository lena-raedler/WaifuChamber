//
// Created by lena on 1/23/20.
//

#ifndef WAIFU_GATE_H
#define WAIFU_GATE_H

#include <utility>
#include <vector>
#include <string>
#include "../utils/utility.h"
#include <iostream>
#include "../GlobalConstants.h"

class Gate {
public:
    Gate& operator=(Gate& g) = default;
    Gate& operator=(Gate&& g) = default;
    Gate(Gate& g) = default;
    Gate(Gate&& g) = default;
    Gate() = default;
    ~Gate() = default;
    Gate(std::pair<int, int> position, std::string path);
    Gate(std::pair<int, int> position, std::string path, bool leftLocked, bool rightLocked);
    Gate(std::pair<int, int> position, std::string path, int keyId);
    vec_t position;
    std::string nextRoomPath;
    std::vector<triangle> hitbox;
    bool leftLocked; //top
    bool rightLocked; //bot
    int keyId = -1;
};


#endif //WAIFU_GATE_H
