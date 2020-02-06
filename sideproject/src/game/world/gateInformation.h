//
// Created by lena on 2/6/20.
//

#ifndef WAIFU_GATEINFORMATION_H
#define WAIFU_GATEINFORMATION_H

#include <vector>
#include <utility>
#include <string>

struct gateInformation {
    std::string gateId;
    std::pair<int, int> position;
    std::string path;
    bool leftLocked;
    bool rightLocked;
    int keyId;
    std::pair<int, int> newPlayerPosition;
};

#endif //WAIFU_GATEINFORMATION_H
