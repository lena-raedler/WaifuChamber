//
// Created by lena on 1/23/20.
//

#include "Gate.h"

Gate::Gate(std::pair<int, int> pos, std::string path) {
    position = {(double) pos.first, (double) pos.second};
    nextRoomPath = path;
    utility::fillDefaultHitbox(hitbox);
}

Gate::Gate(std::pair<int, int> pos, std::string path, bool leftLock, bool rightLock) {
    position = {(double) pos.first, (double) pos.second};
    nextRoomPath = path;
    leftLocked = leftLock;
    rightLocked = rightLock;
    utility::fillDefaultHitbox(hitbox);

    if(leftLocked == rightLocked && rightLocked == true){
        std::cout << "WARNING: Unopenable gate spawned" << std::endl;
    }

}
Gate::Gate(std::pair<int, int> pos, std::string path, int key) {
    utility::fillDefaultHitbox(hitbox);
    position = {(double) pos.first, (double) pos.second};
    nextRoomPath = path;
    leftLocked = true;
    rightLocked = true;
    keyId = key;
}
bool Gate::collide(triangle& t){
    bool out = false;
    for (triangle t2: hitbox){
        t2 += position;
        out = out || utility::triangleTriangleIntersection(t, t2);
    }
    return out;
}

void Gate::warpPlayer(){

}

