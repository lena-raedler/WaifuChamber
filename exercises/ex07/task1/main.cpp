#include "Person.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

std::vector<std::shared_ptr<Person>> createAndFillVector();
std::vector<Person*> mapPersonsWithFor(const std::vector<std::shared_ptr<Person>>& input);
std::vector<Person*> mapPersonsWithMemFn(std::vector<std::shared_ptr<Person>>& input);
std::vector<Person*> mapPersonsWithTransform(std::vector<std::shared_ptr<Person>>& input);
template <class T> void printVector(const T& vectorToPrint);

struct Foo {
    Person* mapPerson(std::shared_ptr<Person>& personToMap) {
        return &*personToMap;
    }
};

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
    std::set<std::shared_ptr<Person>> alreadyProcessed;

    for (const auto& person_ptr : input) {
        if (alreadyProcessed.find(person_ptr) == alreadyProcessed.end()) {
            output.push_back(&*person_ptr);
            alreadyProcessed.insert(person_ptr); 
        }
    }

    return output;
}

// https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
// https://stackoverflow.com/questions/908272/stdback-inserter-for-a-stdset
// https://stackoverflow.com/questions/23579832/why-is-there-no-transform-if-in-the-c-standard-library
std::vector<Person*> mapPersonsWithMemFn(std::vector<std::shared_ptr<Person>>& input) {
    std::set<Person*> outputSet;
    std::vector<Person*> outputVector;
    Foo foo;
    auto mapPersonLambda = std::mem_fn(&Foo::mapPerson);

    std::transform(
            input.begin(),
            input.end(),
            std::inserter(outputSet, outputSet.begin()),
            [&](std::shared_ptr<Person>& person_ptr) -> Person* { return mapPersonLambda(foo, person_ptr); }
            );

    // Remove elements because there exists no transform_if()
    outputVector.assign(outputSet.begin(), outputSet.end());
    return outputVector;
}


// Almost the same as before
std::vector<Person*> mapPersonsWithTransform(std::vector<std::shared_ptr<Person>>& input) {
    std::set<Person*> outputSet;
    std::vector<Person*> outputVector;
    Foo foo;

    std::transform(
            input.begin(),
            input.end(),
            std::inserter(outputSet, outputSet.begin()),
            [&](std::shared_ptr<Person>& person_ptr) -> Person* { return foo.mapPerson(person_ptr); }
    );

    // Remove elements because there exists no transform_if()
    outputVector.assign(outputSet.begin(), outputSet.end());
    return outputVector;
}


// Can only take pointers!
template <class T>
void printVector(const T& vectorToPrint) {
    //std::cout << "Print vector..." << std::endl;
    for (const auto& toPrint : vectorToPrint) {
        std::cout << *toPrint << std::endl;
    }
    std::cout << std::endl;
}