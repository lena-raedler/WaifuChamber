//
// Created by auki on 06.12.19.
//
#include "utility.h"

#include "../world/room.h"
#include "LingeringText.hpp"

namespace utility {
    bool hitboxCollision(std::vector<triangle> a, vec_t posA, std::vector<triangle> b, vec_t posB){
        for(triangle& t: a){
            t+=posA;
        }
        for(triangle& t: b){
            t+=posB;
        }

            for (auto &tri_proj : a) {
                for (auto &tri_mov : b) {
                    if (utility::triangleTriangleIntersection(tri_proj, tri_mov)) {
                        return true;
                    }
                }
            }

        return false;
    }
    bool hitboxCollisionAABB(std::vector<triangle> a, vec_t posA, std::vector<triangle> b, vec_t posB){
        for(triangle& t: a){
            t+=posA;
        }
        for(triangle& t: b){
            t+=posB;
        }
        vec_t aMax = getMax(a);
        vec_t aMin = getMin(a);
        vec_t bMax = getMax(b);
        vec_t bMin = getMin(b);

        if(aMax.y >= bMin.y && aMax.x >= bMin.x && bMax.y >= aMin.y && bMax.x >= aMin.x) {
            for (auto &tri_proj : a) {
                for (auto &tri_mov : b) {
                    if (utility::triangleTriangleIntersection(tri_proj, tri_mov)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    vec_t convert(std::pair<int, int> p){
        return {(double) p.first * GlobalConstants::tileSize, (double) p.second * GlobalConstants::tileSize};
    }

    vec_t convert(int i, int j) {
        return convert({i, j});
    }

    void fillDefaultHitbox(std::vector<triangle>& vec){

        fillDefaultHitbox(vec, 1, 1, {0,0});

    }
    void fillDefaultHitbox(std::vector<triangle>& vec, int x, int y){
        fillDefaultHitbox(vec, x, y, {0,0});

    }
    void fillDefaultHitbox(std::vector<triangle>& vec, int x,int y, vec_t offset){
        {
            triangle t{offset,
                       {static_cast<double>(GlobalConstants::tileSize*x) + offset.x, offset.y},
                       {offset.x,                         static_cast<double>(GlobalConstants::tileSize * y) + offset.y}};
            vec.push_back(t);
        }
        {
            triangle t{{static_cast<double>(GlobalConstants::tileSize * x) + offset.x,  static_cast<double>(GlobalConstants::tileSize * y) + offset.y},
                       {static_cast<double>(GlobalConstants::tileSize * x) + offset.x, offset.y},
                       {offset.x,  static_cast<double>(GlobalConstants::tileSize * y) + offset.y}};
            vec.push_back(t);
        }

    }
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

    Room parseRoom(std::string path, Renderer &renderer, std::pair<int, int> resolution) {
        Room room;
        std::ifstream roomFile(path);
        std::string line;
        SDL_Texture* backgroundTexture;
        SDL_Rect backgroundRectangle;
        std::string gatePath;
        std::vector<std::pair<int, int>> platformPositionVector;
        std::vector<std::pair<std::pair<int, int>, char>> gatePositions;
        std::unordered_map<char, std::string> tileMap;
        std::unordered_map<SDL_Texture*, SDL_Rect> tileRenderMap;
        int lockedWallId = 0;

        while(std::getline(roomFile, line)) {
            if(line.find("ID") != std::string::npos) {
                while(line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if(line.find("END") != std::string::npos) {
                        break;
                    }
                    std::vector<std::string> idInformation;
                    boost::split(idInformation, line, boost::is_any_of("_"));
                    room.roomId = std::atoi(idInformation[1].c_str());
                }
            }
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
                    std::vector<std::string> tileStrings;
                    boost::algorithm::erase_all(line, " ");
                    boost::split(tileStrings, line, boost::is_any_of("="));
                    tilePathPair.first = tileStrings[0].front(); //key
                    tilePathPair.second = tileStrings[1]; //value
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
                        surface = IMG_Load(tilePath.c_str());
                        SDL_Texture* texture = renderer.createTextureFromSurface(surface);
                        SDL_Rect rect = {y, x, GlobalConstants::tileSize, GlobalConstants::tileSize};
                        if(c == 'p') {
                            std::pair<int, int> platformPosition;
                            platformPosition.first = y;
                            platformPosition.second = x;
                            platformPositionVector.push_back(platformPosition);
                        }
                        // regular unlocked doors
                        if(c == 'd') {
                            std::pair<int, int> gatePosition;
                            gatePosition.first = y;
                            gatePosition.second = x;
                            gatePositions.push_back(std::make_pair(gatePosition, c));
                        }
                        if(c == 'e') {
                            std::pair<int, int> gatePosition;
                            gatePosition.first = y;
                            gatePosition.second = x;
                            gatePositions.push_back(std::make_pair(gatePosition, c));
                        }
                        if(c == 'g') {
                            std::pair<int, int> gatePosition;
                            gatePosition.first = y;
                            gatePosition.second = x;
                            gatePositions.push_back(std::make_pair(gatePosition, c));
                        }
                        if(c == 'h') {
                            std::pair<int, int> gatePosition;
                            gatePosition.first = y;
                            gatePosition.second = x;
                            gatePositions.push_back(std::make_pair(gatePosition, c));
                        }
                        if(c == 'y') {
                            std::pair<int, int> gatePosition;
                            gatePosition.first = y;
                            gatePosition.second = x;
                            gatePositions.push_back(std::make_pair(gatePosition, c));
                        }
                        // locked doors
                        if(c == 'l') {
                            std::pair<int, int> gatePosition;
                            gatePosition.first = y;
                            gatePosition.second = x;
                            gatePositions.push_back(std::make_pair(gatePosition, c));
                        }
                        if(c == 'x') {
                            std::pair<int, int> gatePosition;
                            gatePosition.first = y;
                            gatePosition.second = x;
                            gatePositions.push_back(std::make_pair(gatePosition, c));
                        }
                        if(c == 'w') {
                            std::pair<int, int> wallPosition;
                            wallPosition.first =y;
                            wallPosition.second = x;
                            room.wallPostitions.push_back(wallPosition);
                        }
                        if(c == 'c') {
                            std::pair<int, int> ceilingPosition;
                            ceilingPosition.first = y;
                            ceilingPosition.second = x;
                            room.ceilingPositions.push_back(ceilingPosition);
                        }
                        if(c == 'f') {
                            std::pair<int, int> floorPosition;
                            floorPosition.first = y;
                            floorPosition.second = x;
                            room.floorPositions.push_back(floorPosition);
                        }
                        if(c == '<') {
                            LockedWall wall;
                            wall.id = lockedWallId;
                            wall.position.first = y;
                            wall.position.second = x;
                            wall.orientation = true;
                            wall.texture = texture;
                            if(!decode(GlobalObjects::savedVariables.oneways, lockedWallId)) {
                                room.lockedWalls.push_back(wall);
                            } else {
                                SDL_DestroyTexture(texture);
                                break;
                            }

                        }
                        if(c == '>') {
                            LockedWall wall;
                            wall.id = lockedWallId;
                            wall.position.first = y;
                            wall.position.second = x;
                            wall.orientation = false;
                            wall.texture = texture;
                            if(GlobalObjects::savedVariables.oneways == lockedWallId) {
                                room.lockedWalls.push_back(wall);
                            } else {
                                SDL_DestroyTexture(texture);
                                break;
                            }

                        }
                        if(tilePath.find("none") != std::string::npos) {
                            y += GlobalConstants::tileSize;
                            continue;
                        }
                        textureRectanglePair.first = texture;
                        textureRectanglePair.second = rect;
                        tileRenderMap.insert(textureRectanglePair);
                        y += GlobalConstants::tileSize;
                        SDL_FreeSurface(surface);
                    }
                    y = 0;
                    x += GlobalConstants::tileSize;
                }
            }
            else if(line.find("GATES") != std::string::npos) {
                while (line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if (line.find("END") != std::string::npos) {
                        break;
                    }
                    gateInformation allGateInfo;
                    std::string gateLine;
                    std::ifstream gates("files/rooms/gates.txt");
                    while (std::getline(gates, gateLine)) {
                        std::vector<std::string> gateStrings;
                        boost::split(gateStrings, gateLine, boost::is_space());
                        std::string gateNumber = gateStrings[0];
                        while(line.front() == ' ') {
                            boost::algorithm::erase_first(line, " ");
                        }
                        std::vector<std::string> moreGateInfo;
                        boost::split(moreGateInfo, line, boost::is_space());
                        if(boost::algorithm::equals(moreGateInfo[0], gateNumber)) {
                            gatePath = gateStrings[1];
                            room.newStartPosition.first = std::atoi(gateStrings[2].c_str());
                            room.newStartPosition.second = std::atoi(gateStrings[3].c_str());
                            std::pair<std::pair<int, int>, std::string> gateInfo;
                            for(auto i : gatePositions) {
                                if (moreGateInfo[1].front() == i.second) {
                                    if(i.second == 'l' || i.second == 'x') {
                                        allGateInfo.leftLocked = true;
                                        allGateInfo.rightLocked = true;
                                    } else {
                                        allGateInfo.leftLocked = false;
                                        allGateInfo.rightLocked = false;
                                    }
                                    gateInfo.first = i.first;
                                    gateInfo.second = gatePath;
                                    room.doorPositions.push_back(gateInfo);
                                    allGateInfo.gateId = gateNumber;
                                    allGateInfo.keyId = std::atoi(moreGateInfo[2].c_str());
                                    allGateInfo.path = gatePath;
                                    allGateInfo.position = i.first;
                                    allGateInfo.newPlayerPosition.first = std::atoi(gateStrings[2].c_str());
                                    allGateInfo.newPlayerPosition.second = std::atoi(gateStrings[3].c_str());
                                    room.gates.push_back(allGateInfo);
                                } else { continue; }
                            }
                        } else { continue; }

                    }
                }
            }
            else if(line.find("ENEMY") != std::string::npos) {
                while(line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if (line.find("END") != std::string::npos) {
                        break;
                    }
                    EnemyInformation enemies;
                    std::pair<std::pair<int, int>, int> enemyInformation;
                    std::vector<std::string> enemyStrings;
                    while (line.front() == ' ') {
                        boost::algorithm::erase_first(line, " ");
                    }
                    boost::split(enemyStrings, line, boost::is_space());
                    std::pair<int, int> enemyPosition;
                    enemyPosition.first = std::atoi(enemyStrings[1].c_str());
                    enemyPosition.second = std::atoi(enemyStrings[2].c_str());
                    enemyInformation.first = enemyPosition;
                    std::vector<std::string> idInformation;
                    boost::split(idInformation, enemyStrings[0], boost::is_any_of("_"));
                    int enemyId = std::atoi(idInformation[1].c_str());
                    enemyInformation.second = enemyId;
                    room.enemyInformation.push_back(enemyInformation);

                    // here starts the code for the new vector
                    enemies.id = std::atoi(idInformation[1].c_str());
                    enemies.position.first = std::atoi(enemyStrings[1].c_str());
                    enemies.position.second = std::atoi(enemyStrings[2].c_str());
                    if(enemyStrings.size() > 3) {
                        for(size_t i = 3; i < enemyStrings.size(); i++) {
                            std::vector<std::string> patrolPoints;
                            boost::split(patrolPoints, enemyStrings[i], boost::is_any_of(","));
                            std::pair<int, int> patrolPositions;
                            patrolPositions.first = std::atoi(patrolPoints[0].c_str());
                            patrolPositions.second = std::atoi(patrolPoints[1].c_str());
                            enemies.patrolPoints.push_back(patrolPositions);
                        }
                    } else {}
                    room.enemies.push_back(enemies);
                }
            }
            else if(line.find("BOSS") != std::string::npos) {
                while(line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if(line.find("END") != std::string::npos) {
                        break;
                    }
                    std::pair<std::pair<int, int>, int> bossInformation;
                    std::vector<std::string> bossStrings;
                    while(line.front() == ' ') {
                        boost::algorithm::erase_first(line, " ");
                    }
                    boost::split(bossStrings, line, boost::is_space());
                    std::pair<int, int> bossPosition;
                    bossPosition.first = std::atoi(bossStrings[1].c_str());
                    bossPosition.second = std::atoi(bossStrings[2].c_str());
                    bossInformation.first = bossPosition;
                    std::vector<std::string> bossIdStrings;
                    boost::split(bossIdStrings, bossStrings[0], boost::is_any_of("_"));
                    bossInformation.second = std::atoi(bossIdStrings[1].c_str());
                    room.bossInformation.push_back(bossInformation);
                }
            }
            else if(line.find("MUSIC") != std::string::npos) {
                while(line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if(line.find("END") != std::string::npos) {
                        break;
                    }
                    while(line.front() == ' ') {
                        boost::algorithm::erase_first(line, " ");
                    }
                    room.musicId = std::atoi(line.c_str());
                }
            }
            else if(line.find("COORDINATES") != std::string::npos) {
                while(line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if(line.find("END") != std::string::npos) {
                        break;
                    }
                    while(line.front() == ' ') {
                        boost::algorithm::erase_first(line, " ");
                    }
                    std::vector<std::string> roomCoords;
                    boost::split(roomCoords, line, boost::is_any_of(","));
                    room.position.x = std::atoi(roomCoords[0].c_str());
                    room.position.y = std::atoi(roomCoords[1].c_str());
                }
            }
            else if(line.find("PICKUP") != std::string::npos) {
                while(line.find("END") == std::string::npos) {
                    std::getline(roomFile, line);
                    if(line.find("END") != std::string::npos) {
                        break;
                    }
                    while(line.front() == ' ') {
                        boost::algorithm::erase_first(line, " ");
                    }
                    PickupItems pickedUp;
                    std::vector<std::string> pickupStrings;
                    boost::split(pickupStrings, line, boost::is_space());
                    pickedUp.id = std::atoi(pickupStrings[0].c_str());
                    pickedUp.position.x = std::atoi(pickupStrings[1].c_str());
                    pickedUp.position.y = std::atoi(pickupStrings[2].c_str());
                    pickedUp.position.x *= GlobalConstants::tileSize;
                    pickedUp.position.y *= GlobalConstants::tileSize;
                    room.pickupItems.push_back(pickedUp);
                }
            }

        }

        room.platformPositions = platformPositionVector;
        room.backgroundRectangle = backgroundRectangle;
        room.backgroundtexture = backgroundTexture;
        room.tileMap = tileRenderMap;
        lockedWallId++;

        //Room room(backgroundTexture, backgroundRectangle, tileRenderMap, *&platformPositionVector, gate);
        return room;

    }

    Image loadImage(std::string path) {
        return loadImage(path, *GlobalObjects::renderPtr);
    }
    Image loadImage(std::string path, Renderer& renderer) {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface)
            throw std::runtime_error("Could not load surface :(");

        SDL_Texture* texture = renderer.createTextureFromSurface(surface);;
        if (!texture)
            throw std::runtime_error("Could not load texture : /");

        SDL_Rect rect = {0, 0, surface->w, surface->h};
        //SDL_Rect rect = {0, 0, 500, 500};
        SDL_FreeSurface(surface);
        return Image(texture, rect);
    }

    vec_t getMax(std::vector<triangle>& tris){
        vec_t max;
        for(triangle& t : tris){
            vec_t tmp = t.max();
            if(tmp.x > max.x){
                max.x = tmp.x;
            }
            if(tmp.y > max.y){
                max.y = tmp.y;
            }
        }
        return max;
    }
    vec_t getMin(std::vector<triangle>& tris){
        vec_t min;
        for(triangle& t : tris){
            vec_t tmp = t.min();
            if(tmp.x < min.x){
                min.x = tmp.x;
            }
            if(tmp.y < min.y){
                min.y = tmp.y;
            }
        }
        return min;
    }


    // Default font and size
    TTF_Font* loadFont() {
        return loadFont(40);
    }
    TTF_Font* loadFont(int fontSize) {
        return loadFont("files/freefont-20120503/FreeSerif.ttf", fontSize);
    }
    TTF_Font* loadFont(std::string fontPath, int fontSize) {    // TODO Throws error, but still works somehow...
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!font) {
            std::cerr << "Within loadFont(): Failed to load lazy font! SDL_ttf Error: %s" << TTF_GetError() << std::endl;
        }
        //std::cout << TTF_GetFontStyle(font) << std::endl;
        return font;
    }

    SDL_Texture* loadFromRenderedText(TTF_Font* font, std::string textureText, SDL_Color textColor, SDL_Rect& rect) {
        SDL_Texture* fontTexture = nullptr;

        //Render text surface
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
        if (!textSurface) {
            printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        else {
            //Create texture from surface pixels
            fontTexture = SDL_CreateTextureFromSurface(GlobalObjects::renderPtr->getRenderer(), textSurface );
            if (!fontTexture) {
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
            }
            else {
                //Get image dimensions
                rect.w = textSurface->w;
                rect.h = textSurface->h;
            }

            //Get rid of old surface
            SDL_FreeSurface(textSurface);
        }

        return fontTexture;
    }
    //checks if bit lsb-i is set in toDecode
    bool decode(int toDecode, int i) {
        return 1 & (toDecode >> i);
    }

    void encode(int& toEncode, int i){
        toEncode |= (1 << i);
        GlobalObjects::savedVariables.serialize();
    }
    void displayMessage(std::string str, vec_t position, int duration, int id){
        LingeringText keyText;
        keyText.text.changeText(str);
        keyText.text.rect = {static_cast<int>(position.x - 50), static_cast<int>(position.y - 40)};
        keyText.text.changeFontSize(20);
        keyText.id = id;
        keyText.duration = duration;
        keyText.print();
    }
}