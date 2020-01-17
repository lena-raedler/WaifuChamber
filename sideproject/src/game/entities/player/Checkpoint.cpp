#pragma once

#include "Checkpoint.h"
void Checkpoint::event(){
    player.rest();
    player.lastCP = this;
}