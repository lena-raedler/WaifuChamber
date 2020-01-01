//
// Created by lena on 1/1/20.
//

#include "room.h"

Room::Room(std::string path)
    : path(path)
{
    parseRoom();
}

//Room::~Room() {}

void Room::parseRoom() {
    std::ifstream room(path);
    std::string line;
    std::string id;
    while(std::getline(room, line)) {

    }

}