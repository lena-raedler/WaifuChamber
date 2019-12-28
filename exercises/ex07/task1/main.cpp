
#include "Person.hpp"
#include <iostream>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Person>> createVector();
std::vector<Person*> mapPerson(const std::vector<std::shared_ptr<Person>>& input);

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};


int main() {
    //auto r1 = new Resource;
    //Resource r1;

    //std::unique_ptr<Resource> res1(std::make_unique<Resource>(r1));
    //std::unique_ptr<Resource> res2(std::make_unique<Resource>(r1));


    createVector();


    /*
    Person p;
    std::cout << "1" << std::endl;
    std::unique_ptr<Person> ptr1 = std::make_unique<Person>(p);

    std::cout << "2" << std::endl;
    std::unique_ptr<Person> ptr2 = std::make_unique<Person>(p);
     */
}


std::vector<std::shared_ptr<Person>> createVector() {
    std::shared_ptr<Person> person1 = std::make_shared<Person>(new Person {"FirstName2", "LastName2", 2});
    //auto person2 = new Person {"FirstName2", "LastName2", 2};
    //auto person3 = new Person {"FirstName3", "LastName3", 3};

    std::vector<std::shared_ptr<Person>> vector;
    //vector.push_back(std::make_shared<Person>(*person1));
    //vector.push_back(std::make_shared<Person>(*person2));
    //vector.push_back(std::make_shared<Person>(*person3));
    return vector;
}

std::vector<Person*> mapPerson(const std::vector<std::shared_ptr<Person>>& input) {

    // dummy
    std::vector<Person*> output;
    return output;
}