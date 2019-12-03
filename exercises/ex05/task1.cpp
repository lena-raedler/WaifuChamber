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

void printSeparatorLine();

int main(int argc, char *argv[]) {
    // create 5 instances of person
    foo::Person p1{"Roland", "Mitch", 37};
    foo::Person p2{"Carola", "Duck", 50};
    foo::Person p3{"Peter", "Malarkey", 18};
    foo::Person p4{"Larry", "Trunk", 26};
    foo::Person p5{"Sybille", "Macaroni", 33};
    foo::Person p6{"Herbert", "Tungsten", 57};

    // insert into std::vector
    std::cout << "Creating vector with persons 1 to 5" << std::endl;
    printSeparatorLine();
    std::vector<foo::Person> pVector{p1, p2, p3, p4, p5}; //somehow calls nothing

    //insert into std::set
    std::cout << "\nCreating set with same persons" << std::endl;
    printSeparatorLine();
    std::set<foo::Person> set{p1, p2, p3, p4, p5}; // calls <

    //insert into std::map
    std::cout << "\nCreating map with same persons" << std::endl;
    printSeparatorLine();
    std::map<foo::Person, int> map{{p1, 0}, {p2, 0}, {p3, 0}, {p4, 0}, {p5, 0}}; // calls < as well


    // use different standard algorithms on these containers
    std::cout << "\nFinding in vector" << std::endl;
    printSeparatorLine();
    std::find(pVector.begin(), pVector.end(), p5) != pVector.end(); // uses ==

    std::cout << "\nFinding in set" << std::endl;
    printSeparatorLine();
    const bool is_in = set.find(p1) != set.end(); // uses <
    std::find(set.begin(), set.end(), p1); // uses ==

    std::cout << "\nFinding in map" << std::endl;
    printSeparatorLine();
    map.find(p3); // uses <
    //std::find(map.begin(), map.end(), p3); <- dont use this, there is no == operator for pair

    std::cout << "\nPartitioning vector" << std::endl;
    printSeparatorLine();
    std::partition(pVector.begin(), pVector.end(), [](foo::Person& person){ return person.age <= 33;}); // uses nothing again

    //partition on set and map not possible i think

    std::cout << "\nInserting into vector" << std::endl;
    printSeparatorLine();
    pVector.insert(pVector.begin()+1, p6);

    std::cout << "\nInserting into set" << std::endl;
    printSeparatorLine();
    set.insert(p6);

    std::cout << "\nInserting into map" << std::endl;
    printSeparatorLine();
    map.insert({p6, 0});
}

void printSeparatorLine() {
    std::cout << "----------------" << std::endl;
}