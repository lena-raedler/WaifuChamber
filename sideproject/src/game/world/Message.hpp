//
// Created by auki on 27.02.20.
//

#ifndef WAIFU_MESSAGE_HPP
#define WAIFU_MESSAGE_HPP

#include "../utils/LingeringText.hpp"
#include "../GlobalObjects.h"
#include "../entities/player/Movable.h"


class Message {
public:
    LingeringText t;
    Movable m;

    void print(){
        t.text.rect ={ static_cast<int>(m.position.x-40), static_cast<int>(m.position.y-50)};
        t.text.changeText(t.text.message);
        t.print();
    }
};


#endif //WAIFU_MESSAGE_HPP
