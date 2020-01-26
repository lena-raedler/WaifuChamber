//
// Created by auki on 26.01.20.
//

#ifndef WAIFU_SAVEDVARIABLES_H
#define WAIFU_SAVEDVARIABLES_H

#include <memory>
#include <cstring>
#include <fstream>
#include <string>
#include <iostream>

extern void operator>>(std::string& string, int& i);
extern void operator>>(std::string& string, double& d);

struct SavedVariables {
#define SAVE(_type, _identifier, _default) _type _identifier = _default;
#include "SavedVariables.def"
    void serialize(std::ofstream& file){
#define SAVE(_type, _identifier, _default) \
file << _identifier << std::endl;
#include "SavedVariables.def"
    }
    void deSerialize(std::ifstream& file){
        std::string str;
#define SAVE(_type, _identifier, _default) \
if(std::getline(file, str)){; \
str >> _identifier;}
#include "SavedVariables.def"
    }
};


#endif //WAIFU_SAVEDVARIABLES_H
