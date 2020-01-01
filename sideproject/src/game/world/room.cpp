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
    std::ifstream room;
    std::string test;
    room.open(path);
    while(std::getline(room, test)) {
        std::cout << test << std::endl;
    }

}