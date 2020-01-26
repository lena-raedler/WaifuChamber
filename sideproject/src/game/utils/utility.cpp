//
// Created by auki on 06.12.19.
//
#include "utility.h"

#include "../world/room.h"

namespace utility {
    std::vector <value_t> getBarycentricCoordinates(const triangle a,const vec_t b) {
        vec_t v0 = a[1] - a[0];
        vec_t v1 = a[2] - a[0];
        vec_t v2 = b - a[0];
        value_t cramer[5];
        cramer[0] = v0.dot(v0);
        cramer[1] = v0.dot(v1);
        cramer[2] = v1.dot(v1);
        cramer[3] = v2.dot(v0);
        cramer[4] = v2.dot(v1);
        value_t denom = cramer[0] * cramer[2] - cramer[1] * cramer[1];
        double u, v;
        u = (cramer[2] * cramer[3] - cramer[1] * cramer[4]) / denom;
        v = (cramer[0] * cramer[4] - cramer[1] * cramer[3]) / denom;
        return {u, v, 1 - u - v};

    }

    bool pointTriangleIntersection(const triangle a,const vec_t b) {
        auto bary = getBarycentricCoordinates(a, b);
        for (auto d : bary) {
            if (d > 1 || d < 0) {
                return false;
            }
        }
        return true;

    }

    bool lineLineIntersection(const vec_t aStart,const vec_t aEnd,const vec_t bStart,const vec_t bEnd){
        value_t tmp = (aStart.x - aEnd.x)*(bStart.y - bEnd.y) - (aStart.y - aEnd.y)*(bStart.x - bEnd.x);
        if (std::abs(tmp) <= std::numeric_limits<value_t>::epsilon()){
            return false;//parallel
        }
        value_t t,u;
        t = ((aStart.x - bStart.x)*(bStart.y - bEnd.y)-(aStart.y - bStart.y)*(bStart.x - bEnd.x))/tmp;
        u = ((aStart.x - aEnd.x)*(aStart.y - bStart.y)-(aStart.y - aEnd.y)*(aStart.x - bStart.x))/tmp;
        u *= -1; //not sure if this works
        return(t <= 1 && t >= 0 && u <= 1 && u >= 0);
    }
    bool triangleTriangleIntersection(const triangle a, const vec_t offseta, const triangle b, const vec_t offsetb){
        triangle a2 {a[0]+offseta, a[1] + offseta, a[2] + offseta};
        triangle b2 {b[0]+offsetb, b[1] + offsetb, b[2] + offsetb};
        return triangleTriangleIntersection(a2, b2);
    }

    bool triangleTriangleIntersection(const triangle a, const triangle b) {
        for (int i = 0; i < 3; ++i) {
            if (pointTriangleIntersection(a, b[i]) || pointTriangleIntersection(b, a[i])) {
                return true;
            }
        }
        return lineLineIntersection(a[0], a[1], b[0], b[1]) ||
               lineLineIntersection(a[1], a[2], b[0], b[1]) ||
               lineLineIntersection(a[0], a[2], b[0], b[1]) ||
               lineLineIntersection(a[0], a[1], b[1], b[2]) ||
               lineLineIntersection(a[1], a[2], b[1], b[2]) ||
               lineLineIntersection(a[0], a[2], b[1], b[2]) ||
               lineLineIntersection(a[0], a[1], b[0], b[2]) ||
               lineLineIntersection(a[1], a[2], b[0], b[2]) ||
               lineLineIntersection(a[0], a[2], b[0], b[2]);

    }

    Room parseRoom(Room room, std::string path, Renderer &renderer, std::pair<int, int> resolution) {
        std::ifstream roomFile(path);
        std::string line;
        SDL_Texture* backgroundTexture;
        SDL_Rect backgroundRectangle;
        std::string gatePath;
        std::vector<std::pair<int, int>> platformPositionVector;
        std::vector<std::pair<int, int>> gatePositions;
        std::unordered_map<char, std::string> tileMap;
        std::unordered_map<SDL_Texture*, SDL_Rect> tileRenderMap;
        while(std::getline(roomFile, line)) {
            if(line.find("BACKGROUND") != std::string::npos) {
                std::getline(roomFile, line);
                SDL_Surface* surface = IMG_Load(line.c_str());
                backgroundTexture = renderer.createTextureFromSurface(surface);
                backgroundRectangle = {0, 0, resolution.first, resolution.second};
                SDL_FreeSurface(surface);

            }
            else if(line.find("TILES") != std::string::npos) {
                std::pair<char, std::string> tilePathPair;
                while(line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
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
                int x = 0, y = 0;
                while(line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if(line.find("END") != std::string::npos) {
                        break;
                    }
                    line = line.substr(2); // delete the front two whitespaces from the line
                    SDL_Surface* surface;

                    std::pair<SDL_Texture*, SDL_Rect> textureRectanglePair;
                    for(auto& c : line) {
                        std::string tilePath = tileMap.at(c);
                        tilePath += ".png";
                        if(tilePath.find("none") != std::string::npos) {
                            y += surface->h;
                            continue;
                        }
                        surface = IMG_Load(tilePath.c_str());
                        SDL_Texture* texture = renderer.createTextureFromSurface(surface);
                        SDL_Rect rect = {y, x, surface->w, surface->h};
                        if(c == 'p') {
                            std::pair<int, int> platformPosition;
                            platformPosition.first = y;
                            platformPosition.second = x;
                            platformPositionVector.push_back(platformPosition);
                        }
                        if(c == 'd') {
                            std::pair<int, int> gatePosition;
                            gatePosition.first = y;
                            gatePosition.second = x;
                            gatePositions.push_back(gatePosition);
                        }
                        textureRectanglePair.first = texture;
                        textureRectanglePair.second = rect;
                        tileRenderMap.insert(textureRectanglePair);
                        y += surface->h;
                        SDL_FreeSurface(surface);
                    }
                    y = 0;
                    x += surface->w;
                }
            }
            else if(line.find("GATES") != std::string::npos) {
                while (line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if (line.find("END") != std::string::npos) {
                        break;
                    }
                    std::string gateLine;
                    std::ifstream gates("files/rooms/gates.txt");
                    while (std::getline(gates, gateLine)) {
                        std::string gateNumber = gateLine.substr(0, 7);
                        if (line.compare(gateNumber)) {
                            gatePath = gateLine.substr(8);
                        }

                    }
                }
            }
        }
        Gate gate(gatePositions, gatePath);
        room.platformPositions = platformPositionVector;
        room.backgroundRectangle = backgroundRectangle;
        room.backgroundtexture = backgroundTexture;
        room.tileMap = tileRenderMap;
        room.gate = gate;

        //Room room(backgroundTexture, backgroundRectangle, tileRenderMap, *&platformPositionVector, gate);
        return room;

    }

    ImageNew loadImage(std::string path, Renderer& renderer) {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface)
            throw std::runtime_error("Could not load surface :(");

        SDL_Texture* texture = renderer.createTextureFromSurface(surface);;
        if (!texture)
            throw std::runtime_error("Could not load texture : /");

        SDL_Rect rect = {0, 0, surface->w, surface->h};
        //SDL_Rect rect = {0, 0, 500, 500};
        SDL_FreeSurface(surface);
        return ImageNew(texture, rect);
    }


}