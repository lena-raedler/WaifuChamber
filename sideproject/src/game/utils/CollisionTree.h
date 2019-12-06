//
// Created by auki on 06.12.19.
//

#ifndef WAIFU_COLLISIONTREE_H
#define WAIFU_COLLISIONTREE_H
#include <memory>
#include "Vec2.h"
#include <vector>
#include "../entities/player/Movable.h"

class CollisionTree {
    std::vector<std::unique_ptr<CollisionTree>> children;
    std::vector<std::shared_ptr<Movable>> movables;


};


#endif //WAIFU_COLLISIONTREE_H
