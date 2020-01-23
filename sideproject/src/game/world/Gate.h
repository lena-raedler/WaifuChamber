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

class Gate {
public:
    Gate();
    ~Gate();
    Gate(std::vector<std::pair<int, int>> position, std::string path);
private:
    std::vector<std::pair<int, int>> position;
    std::string nextRoomPath;
};


#endif //WAIFU_GATE_H
