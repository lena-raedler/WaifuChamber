//
// Created by lena on 1/23/20.
//

#include "Gate.h"

Gate::Gate(std::pair<int, int> pos, std::string path) {
    position = utility::convert(pos);
    nextRoomPath = path;
}

Gate::Gate(std::pair<int, int> pos, std::string path, bool leftLock, bool rightLock) {
    position = utility::convert(pos);
    nextRoomPath = path;
    leftLocked = leftLock;
    rightLocked = rightLock;

    if(leftLocked == rightLocked && rightLocked == true){
        std::cout << "WARNING: Unopenable gate spawned" << std::endl;
    }

}
Gate::Gate(std::pair<int, int> pos, std::string path, int key) {
    position = utility::convert(pos);
    nextRoomPath = path;
    leftLocked = true;
    rightLocked = true;
    keyId = key;
}

