#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <array>
#include <cstdlib>

#pragma once

template <std::size_t N>
class Vector {
public:
    // default constructor
    Vector<N>() : data{} {}; //c++ automatically initializes with 0

    template <typename ... T>
    Vector(T... args) : data{args...} { // put the values into the data array
        // fails automatically
        static_assert(sizeof...(args) == N);
    }

    std::string to_string() {
        std::string output;
        for(auto i : data) {
            output += std::to_string(i) + " ";
        }
        return output;
    }
    //subscript operators
    double operator[](unsigned pos) const &&{
        return data[pos];
    }
    double operator[](unsigned pos) const & {
        return data[pos];
    }
    double& operator[](unsigned pos) & {
        return data[pos];
    }
    /*Vector<N> operator+(const Vector<N> &rhs) const {
        Vector<N> result;
        for(int i = 0; i < data.size(); ++i) {
            result[i] = data[i] + rhs[i];
        }
        return result;
    }*/


private:
    std::array<double, N> data;
};


// specialization of 1
template <>
class Vector<1> {
    using TT = Vector<1>;
public:
    Vector<1>() : data{} {}; //c++ automatically initializes with 0

    template <typename ... T>
    Vector(T... args) : data{args...} { // put the values into the data array
        // fails automatically
        static_assert(sizeof...(args) == 1);
    }


    std::string to_string() {
        std::string output;
        for(auto i : data) {
            output += std::to_string(i) + " ";
        }
        return output;
    }
    //subscript operators
    double operator[](unsigned pos) const &&{
        return data[pos];
    }
    double operator[](unsigned pos) const & {
        return data[pos];
    }
    double& operator[](unsigned pos) & {
        return data[pos];
    }
    double &x = data[0];


private:
    std::array<double, 1> data;
};

//specialization of 2
template <>
class Vector<2> {
    using TT = Vector<2>;
public:
    Vector<2>() : data{} {};
    template <typename ... T>
    Vector(T... args) : data{args...} { // put the values into the data array
        // fails automatically
        static_assert(sizeof...(args) == 2);
    }


    std::string to_string() {
        std::string output;
        for(auto i : data) {
            output += std::to_string(i) + " ";
        }
        return output;
    }
    //subscript operators
    double operator[](unsigned pos) const &&{
        return data[pos];
    }
    double operator[](unsigned pos) const & {
        return data[pos];
    }
    double& operator[](unsigned pos) & {
        return data[pos];
    }
    double &x = data[0];
    double &y = data[1];


private:
    std::array<double, 2> data;
};

template <long unsigned size>
Vector<size> operator+(const Vector<size> &lhs, const Vector<size> &rhs) {
    Vector<size> result;
    for(int i = 0; i < size; ++i) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}