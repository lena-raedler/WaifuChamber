#include "Person.hpp"
#include <iostream>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Person>> createAndFillVector();
std::vector<Person*> mapPerson(const std::vector<std::shared_ptr<Person>>& input);
void printVector(const std::vector<std::shared_ptr<Person>>& vectorToPrint);


int main() {
    std::cout << "Create vector..." << std::endl;
    auto vector = createAndFillVector();
    std::cout << "Done!" << std::endl;

    printVector(vector);
}

std::vector<std::shared_ptr<Person>> createAndFillVector() {
    auto person1 = std::make_shared<Person>(Person{"FirstName1", "LastName1", 1});
    auto person2 = std::make_shared<Person>(Person{"FirstName2", "LastName2", 2});
    auto person3 = std::make_shared<Person>(Person{"FirstName3", "LastName3", 3});

    std::vector<std::shared_ptr<Person>> vector {person1, person1, person2, person3};
    return vector;
}

std::vector<Person*> mapPerson(const std::vector<std::shared_ptr<Person>>& input) {

    // dummy
    std::vector<Person*> output;
    return output;
}

void printVector(const std::vector<std::shared_ptr<Person>>& vectorToPrint) {
    std::cout << "Print vector: " << std::endl;
    for (const auto& person_ptr : vectorToPrint) {
        std::cout << *person_ptr << std::endl;
    }
}