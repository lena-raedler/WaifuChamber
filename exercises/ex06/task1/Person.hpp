//
// Created by bnorb on 09.12.19.
//

#ifndef EXAMPLE_PERSON_HPP
#define EXAMPLE_PERSON_HPP

struct Person {
    std::string name = "";
    int age = 0;

    Person() = default;
    Person(std::string& name, int age) : name(std::move(name)), age(age) {}
};

std::string to_string(const Person &person) {
    return person.name + ", age: " + std::to_string(person.age);
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    return os << to_string(person) << std::endl;
}
#endif //EXAMPLE_PERSON_HPP
