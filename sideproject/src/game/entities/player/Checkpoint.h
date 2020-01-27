//
// Created by auki on 17.01.20.
//

#ifndef WAIFU_CHECKPOINT_H
#define WAIFU_CHECKPOINT_H

#include "player.h"
#include "../../utils/Vec2.h"
#include "Interactable.h"
class Player;
class Checkpoint : public Interactable {
public:
    Checkpoint(Checkpoint& cp) = default;
    Checkpoint(Checkpoint&& cp) = default;
    Checkpoint (vec_t pos, Player& player) : player(player){
        lockMovement = true;
        position = pos;
    }
    std::string room = "files/rooms/testroom.txt";
    Player& player;


    //todo make 2 different sprites depending on cp active / inactive

    //Override
    void event();

    void render();

    std::vector<triangle> hitbox;

};


#endif //WAIFU_CHECKPOINT_H
