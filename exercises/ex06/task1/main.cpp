
#include <iostream>
#include <string>
#include <utility>
#include "MyVector.cpp"


void printSeparatorLine();

struct Person {
    std::string name = "";
    int age = 0;

    Person() = default;
    Person(std::string& name, int age) : name(std::move(name)), age(age) {}
};


int main () {
    {
        std::cout << "Creating an int vector" << std::endl;
        MyVector<int> vecInt;
        int numbers[5] = {1,2,3,4,5};
        //MyVector<int> vecInt2(numbers, 5);
        //vecInt.prettyPrint();
        //vecInt2.prettyPrint();

        MyVector<int> vecInt3{numbers, 5};
        vecInt3.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Creating a double vector" << std::endl;
        MyVector<double> vecDouble;
    }

    printSeparatorLine();

    {
        std::cout << "Creating a float vector" << std::endl;
        MyVector<float> vecFloat;
    }

    printSeparatorLine();

    {
        std::cout << "Creating a Person vector" << std::endl;
        Person person;
        MyVector<Person> vecPerson;
    }

    printSeparatorLine();

    {
        std::cout << "Testing copy constructor" << std::endl;
        MyVector<int> vec1;
        MyVector<int> vec2(vec1);
        vec2 = vec2;
    }

    printSeparatorLine();

    {
        std::cout << "Testing copy assignment" << std::endl;
        MyVector<int> vec1;
        MyVector<int> vec2;
        vec2 = vec1;
    }

    printSeparatorLine();

    {
        //std::cout << "Testing move assignment" << std::endl;
        //MyVector<int> vec1;
        //MyVector<int> vec2 = std::move(vec1);
    }
}


void printSeparatorLine() {
    std::cout << "\n--------------------------------\n" << std::endl;
}