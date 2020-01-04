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
        if(line.find("BACKGROUND") != std::string::npos) {
            std::getline(room, line);
            texturePath = line;
            std::cout << texturePath << std::endl; // testing purposes
        }
    }

}

void Room::render(Renderer &renderer) {
    surface = IMG_Load(texturePath.c_str());
    texture = renderer.createTextureFromSurface(surface);

    backgroundRectangle = {0,0, surface->w, surface->h};
    renderer.renderTexture(texture, nullptr, &backgroundRectangle);

}