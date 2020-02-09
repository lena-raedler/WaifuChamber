//
// Created by lena on 2/9/20.
//

#ifndef WAIFU_LOCKEDWALL_H
#define WAIFU_LOCKEDWALL_H

#include <utility>

struct LockedWall {
    int id;
    bool orientation; //true = left, false = right
    std::pair<int, int> position;
};

#endif //WAIFU_LOCKEDWALL_H
