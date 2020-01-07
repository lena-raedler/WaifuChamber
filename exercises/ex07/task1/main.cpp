#include "Person.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Person>> createAndFillVector();
std::vector<Person*> mapPersonsWithFor(const std::vector<std::shared_ptr<Person>>& input);
std::vector<Person*> mapPersonsWithMemFn(std::vector<std::shared_ptr<Person>>& input);
std::vector<Person*> mapPersonsWithTransform(std::vector<std::shared_ptr<Person>>& input);
template <class T> void printVector(const T& vectorToPrint);


int main() {
    std::cout << "Create vector..." << std::endl;
    auto vector = createAndFillVector();
    std::cout << "Done!\n" << std::endl;

    std::cout << "Initial vector" << std::endl;
    printVector(vector);

    std::vector<Person*> mappedVector = mapPersonsWithFor(vector);
    std::cout << "Mapped with for loop" << std::endl;
    printVector(mappedVector);

    std::vector<Person*> mappedVector2 = mapPersonsWithMemFn(vector);
    std::cout << "Mapped with MemFn" << std::endl;
    printVector(mappedVector2);

    std::vector<Person*> mappedVector3 = mapPersonsWithTransform(vector);
    std::cout << "Mapped with Transform" << std::endl;
    printVector(mappedVector3);
}

std::vector<std::shared_ptr<Person>> createAndFillVector() {
    auto person1 = std::make_shared<Person>(Person{"Alice", "Miller", 30});
    auto person2 = std::make_shared<Person>(Person{"Bob", "Smith", 27});
    auto person3 = std::make_shared<Person>(Person{"Carla", "Rodriguez", 54});

    std::vector<std::shared_ptr<Person>> vector {person1, person1, person2, person3, person1, person3};
    return vector;
}

std::vector<Person*> mapPersonsWithFor(const std::vector<std::shared_ptr<Person>>& input) {
    std::vector<Person*> output;

    for (auto& person_ptr : input) {
        output.push_back(person_ptr.get());
    }

    return output;
}

// https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
// https://stackoverflow.com/questions/908272/stdback-inserter-for-a-stdset
// https://stackoverflow.com/questions/23579832/why-is-there-no-transform-if-in-the-c-standard-library
std::vector<Person*> mapPersonsWithMemFn(std::vector<std::shared_ptr<Person>>& input) {
    std::vector<Person*> outputVector;

    std::transform(
            input.begin(),
            input.end(),
            std::inserter(outputVector, outputVector.begin()),
            [&](std::shared_ptr<Person>& person_ptr) -> Person* { return  person_ptr.get(); }
            );

    return outputVector;
}

std::vector<Person*> mapPersonsWithTransform(std::vector<std::shared_ptr<Person>>& input) {
    std::vector<Person*> outputVector(input.size());

    std::transform(
            input.begin(),
            input.end(),
            outputVector.begin(),
            std::mem_fn(&std::shared_ptr<Person>::get)
    );

    return outputVector;
}

// Can only take pointers!
template <class T>
void printVector(const T& vectorToPrint) {
    for (const auto& toPrint : vectorToPrint) {
        std::cout << *toPrint << std::endl;
    }
    std::cout << std::endl;
}