//
// Created by auki on 21.01.20.
//
#include <cstring>
#include <iostream>
#include <string>

enum class Fullscreen {
#define EN(_name, _val) _name = _val,
#include "enum.def"
};
struct Config{
#define CONFIG(_type, _identifier, _default) _type _identifier = _default;
#include "config.def"
};

void serialize(Config& c,unsigned char* buffer){
#define CONFIG(_type, _identifier, _default) \
std::memcpy(buffer, &(c._identifier), sizeof(c._identifier)); \
buffer += sizeof(c._identifier);
#include "config.def"
}

void deSerialize(Config& c,unsigned char* buffer){
#define CONFIG(_type, _identifier, _default) \
std::memcpy(&(c._identifier), buffer, sizeof(c._identifier)); \
buffer += sizeof(c._identifier);
#include "config.def"
}


int main() {
    Config con;
    Config con2;
    con.height = 666;
    unsigned char buf[258];
    serialize(con, buf);
    deSerialize(con2, buf);
    std::cout << con2.height << std::endl;
}