
#include <iostream>
#include <ostream>

#include "Person.hpp"
#include "MyVector.cpp"


void printSeparatorLine();



int main () {

    // Used for testing
    int numbers1[1] = {1};
    int numbers3[3] = {1,2,3};
    int numbers5[5] = {1,2,3,4,5};

    {
        std::cout << "Creating an int vector" << std::endl;
        MyVector<int> vecInt;
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
        MyVector<Person> vecPerson;
        //vecPerson.prettyPrint();

        //Person person1;
        //person1.name = "MyFancyName";
        //person1.age = 21;

        //Person p = {};
        //Person persons[1] = {person1};
        //MyVector<Person> vecPerson{persons, 1};
        //vecPerson.prettyPrint();
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

    printSeparatorLine();

    {
        std::cout << "Testing prettyPrint" << std::endl;
        MyVector<int> vecInt2{numbers5, 5};
        vecInt2.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Test size()" << std::endl;

        std::cout << "Create an empty int vector" << std::endl;
        MyVector<int> vecInt;
        std::cout << "Size: " << vecInt.size() << std::endl;

        std::cout << "Create an int vector with 1 element" << std::endl;
        MyVector<int> vecInt1 {numbers1, 1};
        std::cout << "Size: " << vecInt1.size() << std::endl;

        std::cout << "Create an int vector with 3 elements" << std::endl;
        MyVector<int> vecInt2 {numbers3, 3};
        std::cout << "Size: " << vecInt2.size() << std::endl;

        std::cout << "Create an int vector with 5 elements" << std::endl;
        MyVector<int> vecInt3 {numbers5, 5};
        std::cout << "Size: " << vecInt3.size() << std::endl;
    }

    printSeparatorLine();

    {
        std::cout << "Testing push_back()" << std::endl;
        int numbers[1] = {1};
        MyVector<int> vecInt {numbers, 1};
        vecInt.prettyPrint();

        vecInt.push_back(21);
        vecInt.prettyPrint();

        vecInt.push_back(-83);
        vecInt.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Test pop_back()" << std::endl;
        int numbers[5] = {1,2,3,4,5};
        MyVector<int> vecInt {numbers, 5};
        vecInt.prettyPrint();
        vecInt.pop_back();
        vecInt.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Test erase()" << std::endl;
        int numbers[5] = {1,2,3,4,5};
        MyVector<int> vecInt {numbers, 5};
        vecInt.prettyPrint();
        vecInt.erase(-1);   // Does nothing because out of range
        vecInt.erase(2);
        vecInt.erase(5);    // Does nothing because out of range
        vecInt.prettyPrint();
    }
}


void printSeparatorLine() {
    std::cout << "\n--------------------------------\n" << std::endl;
}