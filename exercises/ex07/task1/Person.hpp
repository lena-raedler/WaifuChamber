#pragma once

#include <iostream>
#include <string>

struct Person {
    std::string first_name;
    std::string last_name;
    int age;
};

std::string to_string(const Person &person) {
    return "Name: " + person.first_name + ' ' + person.last_name + ", Age: " + std::to_string(person.age);
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    return os << to_string(person) << std::endl;
}