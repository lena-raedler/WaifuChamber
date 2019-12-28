#include "Person.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

std::vector<std::shared_ptr<Person>> createAndFillVector();
std::vector<Person*> mapPersonWithFor(const std::vector<std::shared_ptr<Person>>& input);
std::vector<Person*> mapPersonsWithMemFn(const std::vector<std::shared_ptr<Person>>& input);
template <class T> void printVector(const T& vectorToPrint);

Person* mapPerson(const std::shared_ptr<Person>& personToMap);

struct Foo {
    Person* mapPerson(const std::shared_ptr<Person>& personToMap) {
        return &*personToMap;
    }
};

int main() {
    std::cout << "Create vector..." << std::endl;
    auto vector = createAndFillVector();
    std::cout << "Done!\n" << std::endl;

    printVector(vector);

    std::vector<Person*> mappedVector = mapPersonWithFor(vector);
    printVector(mappedVector);
}

std::vector<std::shared_ptr<Person>> createAndFillVector() {
    auto person1 = std::make_shared<Person>(Person{"FirstName1", "LastName1", 1});
    auto person2 = std::make_shared<Person>(Person{"FirstName2", "LastName2", 2});
    auto person3 = std::make_shared<Person>(Person{"FirstName3", "LastName3", 3});

    std::vector<std::shared_ptr<Person>> vector {person1, person1, person2, person3, person1, person3};
    return vector;
}

std::vector<Person*> mapPersonWithFor(const std::vector<std::shared_ptr<Person>>& input) {
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

std::vector<Person*> mapPersonsWithMemFn(const std::vector<std::shared_ptr<Person>>& input) {
    std::vector<Person*> output;

    std::transform(input.begin(), input.end(), input.begin(),
            [](const std::shared_ptr<Person>&) -> Person* { return std::mem_fn(&Foo::mapPerson) });

    return output;
}

// Can only take pointers!
template <class T>
void printVector(const T& vectorToPrint) {
    std::cout << "Print vector..." << std::endl;
    for (const auto& toPrint : vectorToPrint) {
        std::cout << *toPrint << std::endl;
    }
    std::cout << std::endl;
}