//
// Created by auki on 26.01.20.
//

#include "SavedVariables.h"

void operator>>(std::string& string, int& i){
    i =  std::stoi(string);
}
void operator>>(std::string& string, double& d){
    d =  std::stod(string);
}
