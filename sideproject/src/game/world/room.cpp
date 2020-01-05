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
    int row = 0;
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
                line = line.substr(2);
                layoutMatrix.push_back({});
                for(auto & c : line) {
                    layoutMatrix[row].emplace_back(c);
                }
                row++;

            }
        }
    }
    std::cout << layoutMatrix.size() << std::endl;
    std::cout << tileMap.size() << std::endl;
}

void Room::render(Renderer &renderer) {
    surface = IMG_Load(texturePath.c_str());
    texture = renderer.createTextureFromSurface(surface);

    backgroundRectangle = {0,0, surface->w, surface->h};
    renderer.renderTexture(texture, nullptr, &backgroundRectangle);

    // loop through the matrix and check which path is needed
    int x = 0;
    int y = 0;
    for(unsigned int r = 0; r < layoutMatrix.size(); r++) {
        for(unsigned int c = 0; c < layoutMatrix[r].size(); c++) {
            std::string tilePath = tileMap.at(layoutMatrix[r][c]);
            if(tilePath.find("none") != std::string::npos) {
                y += tileSurface->w;
                continue;
            }
            tilePath += ".png";
            tileSurface = IMG_Load(tilePath.c_str());
            SDL_Texture* t = renderer.createTextureFromSurface(tileSurface);
            SDL_Rect rect = {y, x, tileSurface->w, tileSurface->h };
            renderer.renderTexture(t, nullptr, &rect);
            y += tileSurface->h;
        }
        y = 0;
        x += tileSurface->w;
    }

}