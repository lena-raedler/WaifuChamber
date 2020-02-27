//
// Created by auki on 27.02.20.
//

#ifndef WAIFU_LINGERINGTEXT_HPP
#define WAIFU_LINGERINGTEXT_HPP


#include "Text.hpp"
#include "../GlobalObjects.h"

class LingeringText {
public:
    Text text;
    double duration;
    int id = -1;

    void upkeep(double delta){
        duration -= delta;
    }
    void render(){
        text.render();
    }
    void print() {
        bool found = false;
        for (auto &o: GlobalObjects::texts) {
            if (id == o.id) {
                found = true;
                break;
            }
        }
        if(!found){
            GlobalObjects::texts.push_back(*this);
        }
    }
};


#endif //WAIFU_LINGERINGTEXT_HPP
