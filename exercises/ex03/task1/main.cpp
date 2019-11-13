//
// Created by bnorb on 13.11.19.
//

#include "main.hpp"
#include "unique_ptr_to_vec2.hpp"

int main() {
    unique_ptr_to_vec2 ptr = unique_ptr_to_vec2(0, 0);
    ptr.print();
}