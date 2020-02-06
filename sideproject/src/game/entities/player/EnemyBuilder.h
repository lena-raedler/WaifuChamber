//
// Created by auki on 27.01.20.
//

#ifndef WAIFU_ENEMYBUILDER_H
#define WAIFU_ENEMYBUILDER_H
#include "Enemy.h"
#include <vector>

namespace EnemyBuilder {

    extern void buildEnemy(std::vector<std::shared_ptr<Enemy>>& vece, int id, std::pair<int, int> pos);
};


#endif //WAIFU_ENEMYBUILDER_H
