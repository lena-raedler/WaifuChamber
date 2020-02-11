//
// Created by lena on 2/11/20.
//

#ifndef WAIFU_ENEMYINFORMATION_H
#define WAIFU_ENEMYINFORMATION_H

#include <utility>
#include <vector>

struct EnemyInformation {
    int id;
    std::pair<int, int> position;
    std::vector<std::pair<int, int>> patrolPoints;
    // maybe add texture and rectangle for the enemy here
};

#endif //WAIFU_ENEMYINFORMATION_H
