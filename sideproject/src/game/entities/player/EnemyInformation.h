//
// Created by lena on 2/11/20.
//

#ifndef WAIFU_ENEMYINFORMATION_H
#define WAIFU_ENEMYINFORMATION_H

#include <utility>

struct EnemyInformation {
    int id;
    std::pair<int, int> position;
    std::pair<int, int> patrolStartPosition;
    std::pair<int, int> patrolEndPosition;
    // maybe add texture and rectangle for the enemy here
};

#endif //WAIFU_ENEMYINFORMATION_H
