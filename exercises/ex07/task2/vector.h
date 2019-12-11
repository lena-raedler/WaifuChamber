#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <array>

#pragma once

template <std::size_t N>
class Vector {
public:
    // default constructor
    Vector<N>() : data{} {};

    template <typename ... T>
    Vector(T... args) : data{args...} {
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

private:
    std::array<double, N> data;
};


/*TODO:
 * componentwise addition
 * to_string
 * default construction -> elements initialized to 0
 * copy/move constructors --> should be already used (std)
 * additional constructor that takes N doubles to init data
 * subscript operator
 * testing
 * */