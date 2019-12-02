//
// Created by lena on 11/23/19.
//

#include "Person.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>
#include <list>
#include <set>
#include <chrono>
#include <fstream>
#include <algorithm>

struct PersonHash{
    size_t operator()(const Person &p) const{
        return std::hash<std::string>{}(p.last_name);//only lastname, its the only thing we change anyway
    }
};

int main(int argc, char *argv[]) {
    std::ofstream ofVector;
    std::ofstream ofUnordered;
    std::ofstream ofSet;
    std::ofstream ofList;
    std::ofstream ofVectorLookup;
    std::ofstream ofUnorderedLookup;
    std::ofstream ofSetLookup;
    std::ofstream ofListLookup;
    ofVector.open("vec.g");
    ofUnordered.open("unordered.g");
    ofSet.open("set.g");
    ofList.open("list.g");
    ofVectorLookup.open("vecl.g");
    ofUnorderedLookup.open("unorderedl.g");
    ofSetLookup.open("setl.g");
    ofListLookup.open("listl.g");

    for(int i = 128; i < 1000000; i*=2){
        std::vector<Person> vecP;
        auto start = std::chrono::high_resolution_clock::now();
        for(int j = 0; j < i; ++j){
            vecP.reserve(i);
            vecP.push_back(Person{"A", std::to_string(j), 1});
        }
        auto end = std::chrono::high_resolution_clock::now();
        double d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        ofVector << i  <<  " "  <<  d << std::endl;

        std::unordered_set<Person, PersonHash> usetP;
        start = std::chrono::high_resolution_clock::now();
        for(int j = 0; j < i; ++j){
            usetP.insert(Person{"A", std::to_string(j), 1});
        }
        end = std::chrono::high_resolution_clock::now();
        d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        ofUnordered << i  <<  " "  <<  d << std::endl;

        std::list<Person> listP;
        start = std::chrono::high_resolution_clock::now();
        for(int j = 0; j < i; ++j){
            listP.push_back(Person{"A", std::to_string(j), 1});
        }
        end = std::chrono::high_resolution_clock::now();
        d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        ofList << i  <<  " "  <<  d << std::endl;

        std::set<Person> setP;
        start = std::chrono::high_resolution_clock::now();
        for(int j = 0; j < i; ++j){
            setP.insert(Person{"A", std::to_string(j), 1});
        }
        end = std::chrono::high_resolution_clock::now();
        d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        ofSet << i  <<  " "  <<  d << std::endl;

        Person first{"A", "A", 0};
        Person middle{"A", "A", i/2};
        Person last{"A", "A", i-1};

        start = std::chrono::high_resolution_clock::now();
        std::find(std::begin(vecP), std::end(vecP), first);
        std::find(std::begin(vecP), vecP.end(), middle);
        std::find(std::begin(vecP), vecP.end(), last);
        end = std::chrono::high_resolution_clock::now();
        d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        ofVectorLookup << i  <<  " "  <<  d << std::endl;

        start = std::chrono::high_resolution_clock::now();
        std::find(usetP.begin(), usetP.end(), first);
        std::find(usetP.begin(), usetP.end(), middle);
        std::find(usetP.begin(), usetP.end(), last);
        end = std::chrono::high_resolution_clock::now();
        d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        ofUnorderedLookup << i  <<  " "  <<  d << std::endl;

        start = std::chrono::high_resolution_clock::now();
        std::find(listP.begin(), listP.end(), first);
        std::find(listP.begin(), listP.end(), middle);
        std::find(listP.begin(), listP.end(), last);
        end = std::chrono::high_resolution_clock::now();
        d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        ofListLookup << i  <<  " "  <<  d << std::endl;

        start = std::chrono::high_resolution_clock::now();
        std::find(setP.begin(), setP.end(), first);
        std::find(setP.begin(), setP.end(), middle);
        std::find(setP.begin(), setP.end(), last);
        end = std::chrono::high_resolution_clock::now();
        d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        ofSetLookup << i  <<  " "  <<  d << std::endl;


    }
        ofVector.close();
        ofUnordered.close();
        ofSet.close();
        ofList.close();
        ofVectorLookup.close();
        ofUnorderedLookup.close();
        ofSetLookup.close();
        ofListLookup.close();
}