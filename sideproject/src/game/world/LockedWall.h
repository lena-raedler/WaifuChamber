//
// Created by lena on 2/9/20.
//

#ifndef WAIFU_LOCKEDWALL_H
#define WAIFU_LOCKEDWALL_H

#include "../utils/utility.h"
#include "../SavedVariables.h"
#include <utility>


struct LockedWall {
    int id;
    bool orientation; //true = left, false = right
    std::pair<int, int> position;
    vec_t pos_double;
    bool closed = true;
    std::vector<triangle> hitboxOpen;
    std::vector<triangle> hitbox;

    void init();


    void unlock(vec_t pos);
};

#endif //WAIFU_LOCKEDWALL_H
