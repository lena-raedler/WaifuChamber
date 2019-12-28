#include "Person.hpp"
#include <iostream>
#include <set>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Person>> createAndFillVector();
std::vector<Person*> mapPerson(const std::vector<std::shared_ptr<Person>>& input);
void printSharedVector(const std::vector<std::shared_ptr<Person>>& vectorToPrint);
void printVector(const std::vector<Person*>& vectorToPrint);


int main() {
    std::cout << "Create vector..." << std::endl;
    auto vector = createAndFillVector();
    std::cout << "Done!\n" << std::endl;

    printSharedVector(vector);

    std::vector<Person*> mappedVector = mapPerson(vector);
    printVector(mappedVector);
}

std::vector<std::shared_ptr<Person>> createAndFillVector() {
    auto person1 = std::make_shared<Person>(Person{"FirstName1", "LastName1", 1});
    auto person2 = std::make_shared<Person>(Person{"FirstName2", "LastName2", 2});
    auto person3 = std::make_shared<Person>(Person{"FirstName3", "LastName3", 3});

    std::vector<std::shared_ptr<Person>> vector {person1, person1, person2, person3};
    return vector;
}

std::vector<Person*> mapPerson(const std::vector<std::shared_ptr<Person>>& input) {
    std::vector<Person*> output;
    std::set<std::shared_ptr<Person>> alreadyProcessed;

    for (const auto& person_ptr : input) {
        if (alreadyProcessed.find(person_ptr) == alreadyProcessed.end()) {
            output.push_back(&*person_ptr);
            alreadyProcessed.insert(person_ptr); 
        }
    }

    return output;
}

void printSharedVector(const std::vector<std::shared_ptr<Person>>& vectorToPrint) {
    std::cout << "Print shared vector: " << std::endl;
    for (const auto& person_ptr : vectorToPrint) {
        std::cout << *person_ptr << std::endl;
    }
    std::cout << std::endl;
}

void printVector(const std::vector<Person*>& vectorToPrint) {
    std::cout << "Print vector: " << std::endl;
    for (const Person* person : vectorToPrint) {
        std::cout << *person << std::endl;
    }
    std::cout << std::endl;
}