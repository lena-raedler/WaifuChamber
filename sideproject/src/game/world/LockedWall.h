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
    SDL_Texture* texture;

    void init();


    void unlock(vec_t pos);

    bool operator== (const LockedWall& other) const {
        if(id == other.id) {
            return true;
        } else {
            return false;
        }
    }
};

#endif //WAIFU_LOCKEDWALL_H
