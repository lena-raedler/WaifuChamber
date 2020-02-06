#pragma once

#include "Checkpoint.h"
void Checkpoint::event(){
    player.rest();
    std::cout << "rested" << std::endl;
    player.lastCP = this;
}