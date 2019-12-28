
#include "Person.hpp"
#include <iostream>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Person>> createVector();
std::vector<Person*> mapPerson(const std::vector<std::shared_ptr<Person>>& input);


int main() {
    createVector();
}


std::vector<std::shared_ptr<Person>> createVector() {
    std::shared_ptr<Person> person1 = std::make_shared<Person>(new Person {"FirstName2", "LastName2", 2});

    std::vector<std::shared_ptr<Person>> vector
    return vector;
}

std::vector<Person*> mapPerson(const std::vector<std::shared_ptr<Person>>& input) {

    // dummy
    std::vector<Person*> output;
    return output;
}