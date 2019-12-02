//
// Created by lena on 11/23/19.
//

#ifndef WAIFUCHAMBER_PERSON_H
#define WAIFUCHAMBER_PERSON_H


#include <iostream>
#include <memory>
#include <string>



struct Person {
        std::string first_name;
        std::string last_name;
        int age;


        size_t operator()(const Person &p) const{
            return std::hash<std::string>{}(last_name);//only lastname, its the only thing we change anyway
        }
        // override ==
        bool operator==(const Person &p) const {
            return (!first_name.compare(p.first_name) && !last_name.compare(p.last_name) && age == p.age);
        }

        // override !=
        bool operator!=(const Person &p) const {
            return (first_name.compare(p.first_name) && last_name.compare(p.last_name) && age != p.age);
        }

        //override <
        bool operator<(const Person &p) const {
            return (first_name.compare(p.first_name) && last_name.compare(p.last_name) && age < p.age);
        }

        //override >
        bool operator>(const Person &p) const {
            return (first_name.compare(p.first_name) && last_name.compare(p.last_name) && age > p.age);
        }

        //override <=
        bool operator<=(const Person &p) const {
            return !(!first_name.compare(p.first_name) && !last_name.compare(p.last_name) && age < p.age ||
                     age == p.age);
        }

        // override >=
        bool operator>=(const Person &p) const {
            return (!first_name.compare(p.first_name) && !last_name.compare(p.last_name) && age > p.age ||
                    age == p.age);
        }
    };

// implement function to_string for Person based on to_string for simple types
    std::string to_string(const Person &person) {
        return person.first_name + ' ' + person.last_name + ", age: " + std::to_string(person.age);
    }

// override ostream
std::ostream& operator<<(std::ostream& os, const Person& person) {
    return os << to_string(person) << std::endl;
}

#endif //WAIFUCHAMBER_PERSON_H
