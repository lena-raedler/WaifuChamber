//
// Created by auki on 27.02.20.
//

#ifndef WAIFU_PICKUP_HPP
#define WAIFU_PICKUP_HPP


#include "Movable.h"

class Pickup {
public:
    Movable m;
    int id;
    std::string name;
    void (*pFunction)(void);
    void collect(){
        (this->pFunction)();
    }
};


#endif //WAIFU_PICKUP_HPP
