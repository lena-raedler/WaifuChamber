
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

    double numbersDouble1[1] = {1.5};
    double numbersDouble3[3] = {1.5, 2.5, 3.5};
    double numbersDouble5[5] = {1.5, 2.5, 3.5, 4.5, 5.5};

    Person person1 {"MyFancyName1", 21};
    Person person2 {"MyFancyName2", 37};
    Person person3 {"MyFancyName3", 54};
    Person persons[3] = {person1, person2, person3};

    {
        std::cout << "Creating a default int vector and one with {1,2,3}" << std::endl;
        MyVector<int> vecInt;
        vecInt.prettyPrint();
        MyVector<int> vecInt3 = {numbers3, 3};
        vecInt3.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Creating a default double vector and one with {1.0, 2.0, 3.0}" << std::endl;
        MyVector<double> vecDouble;
        vecDouble.prettyPrint();
        MyVector<double> vecDouble3 = {numbersDouble3, 3};
        vecDouble3.prettyPrint();
    }

    printSeparatorLine();

    {
        // TODO Throws errors
        std::cout << "Creating a Person vector" << std::endl;
        MyVector<Person> vecPerson;
        vecPerson.prettyPrint();
        //MyVector<Person> vecPerson3 = {persons, 3};
    }

    printSeparatorLine();

    {
        std::cout << "Test copy- constructor and assignment" << std::endl;
        MyVector<int> vecInt11 = {numbers1, 1};
        std::cout << "vecInt11 : "; vecInt11.prettyPrint();

        std::cout << "Copy vecInt11 to vecInt12" << std::endl;
        MyVector<int> vecInt12(vecInt11);
        std::cout << "vecInt12 : "; vecInt12.prettyPrint();

        std::cout << "Self assign vecInt12. Has no effect" << std::endl;
        vecInt12 = vecInt12;    // Self assignment has no effect
    }

    printSeparatorLine();

    {
        std::cout << "Test move constructor" << std::endl;
        MyVector<int> vecInt31 = {numbers3, 3};
        std::cout << "vecInt31 : "; vecInt31.prettyPrint();
        std::cout << "Move construct vecInt31 to vecInt32" << std::endl;
        //MyVector<int> vecInt32(std::move(vecInt31));
        //std::cout << "vecInt32 : "; vecInt32.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Test move assignment" << std::endl;
        MyVector<double> vecDouble3 = {numbersDouble3, 3};
        MyVector<double> vecDouble5 = {numbersDouble5, 5};
        std::cout << "vecDouble3 : "; vecDouble3.prettyPrint();
        std::cout << "vecDouble5 : "; vecDouble5.prettyPrint();
        std::cout << "Move vecDouble5 to vecDouble3" << std::endl;
        vecDouble3 = std::move(vecDouble5);
        std::cout << "vecDouble3 : "; vecDouble3.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Test prettyPrint" << std::endl;
        MyVector<int> vecInt5{numbers5, 5};
        vecInt5.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Test at(), [], front() and back()" << std::endl;
        MyVector<int> vecInt {numbers3, 3};
        vecInt.prettyPrint();
        std::cout << "vecInt.at(1) : " << vecInt.at(1) << std::endl;
        std::cout << "vecInt[1] : " << vecInt[1] << std::endl;
        std::cout << "vecInt.front() : " << vecInt.front() << std::endl;
        std::cout << "vecInt.back() : " << vecInt.back() << std::endl;

        //MyVector<int>::iterator2<int*> it = vecInt.begin();
        //MyVector<int>::iterator it = vecInt.begin();
    }

    printSeparatorLine();

    {
        std::cout << "Test size() and maxSize()" << std::endl;

        std::cout << "Create an empty int vector" << std::endl;
        MyVector<int> vecInt;
        std::cout << "Size: " << vecInt.size() << std::endl;
        std::cout << "Max size: " << vecInt.max_size() << std::endl;

        std::cout << "Create an int vector with 1 element" << std::endl;
        MyVector<int> vecInt1 {numbers1, 1};
        vecInt1.prettyPrint();
        std::cout << "Size: " << vecInt1.size() << std::endl;

        std::cout << "Create an int vector with 3 elements" << std::endl;
        MyVector<int> vecInt3 {numbers3, 3};
        vecInt3.prettyPrint();
        std::cout << "Size: " << vecInt3.size() << std::endl;

        std::cout << "Create an int vector with 5 elements" << std::endl;
        MyVector<int> vecInt5 {numbers5, 5};
        vecInt5.prettyPrint();
        std::cout << "Size: " << vecInt5.size() << std::endl;
    }

    printSeparatorLine();

    {
        std::cout << "Test empty()" << std::endl;
        MyVector<double> vecDouble1;
        vecDouble1.prettyPrint();
        std::cout << "Empty? : " << vecDouble1.empty() << std::endl;

        MyVector<double> vecDouble2 {numbersDouble1, 1};
        std::cout << "Empty? : " << vecDouble2.empty() << std::endl;
    }

    printSeparatorLine();

    {
        std::cout << "Test clear()" << std::endl;
        MyVector<double> vecDouble1 {numbersDouble3, 3};
        std::cout << "Size: " << vecDouble1.size() << std::endl;
        vecDouble1.prettyPrint();
        std::cout << "Clear all elements" << std::endl;
        vecDouble1.clear();
        std::cout << "Size: " << vecDouble1.size() << std::endl;
        vecDouble1.prettyPrint();
    }

    printSeparatorLine();

    {
        std::cout << "Test push_back()" << std::endl;
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

    printSeparatorLine();

    {
        std::cout << "Adding up vectors" << std::endl;
        MyVector<double> doubleVec(numbersDouble5,5);
        MyVector<int> intVec(numbers5, 5);
        auto whatAmI = intVec + doubleVec;

        doubleVec.prettyPrint();
        std::cout << " + " << std::endl;
        intVec.prettyPrint();
        std::cout << " = " << std::endl;
        whatAmI.prettyPrint();
    }
    printSeparatorLine();
}


void printSeparatorLine() {
    std::cout << "\n--------------------------------\n" << std::endl;
}