
#include "Person.hpp"
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Person>> createVector();

int main() {
    createVector(); 
}


std::vector<std::shared_ptr<Person>> createVector() {
    Person person1 = {"FirstName1", "LastName1", 1};
    Person person2 = {"FirstName2", "LastName2", 2};
    Person person3 = {"FirstName3", "LastName3", 3};
    Person person4 = {"FirstName4", "LastName4", 4};
    Person person5 = {"FirstName5", "LastName5", 5};
    std::vector<std::shared_ptr<Person>> vector;
    vector.push_back(std::make_shared<Person>(person1));
    vector.push_back(std::make_shared<Person>(person1));
    return vector;
}   

