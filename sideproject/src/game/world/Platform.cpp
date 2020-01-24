//
// Created by auki on 24.01.20.
//

#include "Platform.h"
Platform::Platform(std::pair<int,int> p, bool semi){
    value_t x = p.first;
    value_t y = p.second;

    top = {{x, y},{x + GlobalConstants::tileSize, y}, {x, y+GlobalConstants::tileSize}};
    bot = {{x + GlobalConstants::tileSize, y + GlobalConstants::tileSize},{x + GlobalConstants::tileSize, y}, {x, y+GlobalConstants::tileSize}};
    semisolid = semi;
}
std::pair<bool, bool> Platform::direction(Movable& m){//false = left / up
    bool vertical = false;//TODO implement
    bool horizontal = false;
    return std::make_pair(vertical, horizontal);
}
bool Platform::collide(triangle& t){
    return utility::triangleTriangleIntersection(top, t) || utility::triangleTriangleIntersection(bot, t);

}

