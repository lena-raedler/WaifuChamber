//
// Created by auki on 24.01.20.
//

#include "Platform.h"
Platform::Platform(std::pair<int,int> p, bool semi){
    pos[0].x = p.first * GlobalConstants::tileSize;
    pos[0].y = p.second * GlobalConstants::tileSize;

    pos[1].x = pos[0].x + GlobalConstants::tileSize;
    pos[1].y = pos[0].y;

    pos[2].x = pos[0].x;
    pos[2].y = pos[0].y + GlobalConstants::tileSize;

    pos[3].x = pos[1].x;
    pos[3].y = pos[2].y;

    semisolid = semi;
}