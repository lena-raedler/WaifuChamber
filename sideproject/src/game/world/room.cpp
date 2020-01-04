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
    std::pair<char, std::string> tilePathPair;
    while(std::getline(room, line)) {
        if(line.find("BACKGROUND") != std::string::npos) {
            std::getline(room, line);
            texturePath = line;
        }
        else if(line.find("TILES") != std::string::npos) {
            while (line.find("END") == std::string::npos) {
                std::getline(room, line);

                if(line.find("END") != std::string::npos) {
                    break;
                }
                char key = char(line[2]);
                std::string value = line.substr(6);
                tilePathPair.first = key;
                tilePathPair.second = value;
                tileMap.insert(tilePathPair);
            }
        }
        else if(line.find("LAYOUT") != std::string::npos) {
            while(line.find("END") == std::string::npos) {
                std::getline(room, line);
                if(line.find("END") != std::string::npos) {
                    break;
                }
            }
        }
    }
    std::cout << tileMap.size() << std::endl;
}

void Room::render(Renderer &renderer) {
    surface = IMG_Load(texturePath.c_str());
    texture = renderer.createTextureFromSurface(surface);

    backgroundRectangle = {0,0, surface->w, surface->h};
    renderer.renderTexture(texture, nullptr, &backgroundRectangle);

}