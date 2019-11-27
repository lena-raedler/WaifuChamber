//
// Created by lena on 11/27/19.
//

#include "../ex04/task1/Person.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>

int main(int argc, char *argv[]) {
    // create 5 instances of person
    foo::Person p1{"Roland", "Mitch", 37};
    foo::Person p2{"Carola", "Duck", 50};
    foo::Person p3{"Peter", "Malarkey", 18};
    foo::Person p4{"Larry", "Trunk", 26};
    foo::Person p5{"Sybille", "Macaroni", 33};

    // insert into std::vector
    std::cout << "creating vector with persons 1 to 5" << std::endl;
    std::vector<foo::Person> pVector{p1, p2, p3, p4, p5}; //somehow calls nothing

    //insert into std::set
    std::cout << "creating set with same persons" << std::endl;
    std::set<foo::Person> set{p1, p2, p3, p4, p5}; // calls <

    //insert into std::map
    std::cout << "creating map with same persons" << std::endl;
    std::map<foo::Person, int> map{{p1, 0}, {p2, 0}, {p3, 0}, {p4, 0}, {p5, 0}}; // calls < as well


    // use different standard algorithms on these containers
    std::cout << "finding in vector" << std::endl;
    std::find(pVector.begin(), pVector.end(), p5) != pVector.end(); // uses ==

    std::cout << "finding in set" << std::endl;
    const bool is_in = set.find(p1) != set.end(); // uses <
    std::find(set.begin(), set.end(), p1); // uses ==

    std::cout << "finding in map" << std::endl;
    map.find(p3); // uses <
    //std::find(map.begin(), map.end(), p3); <- dont use this, there is no == operator for pair

    std::cout << "partitioning vector" << std::endl;
    std::partition(pVector.begin(), pVector.end(), [](foo::Person& person){ return person.age <= 33;}); // uses nothing again

    //partition on set and map not possible i think
}