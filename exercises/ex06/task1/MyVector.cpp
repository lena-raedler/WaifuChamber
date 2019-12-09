//
// Created by bnorb on 08.12.19.
//

//#include "MyVector.hpp"
#include <cstring>

template <typename T, int Length>
class MyVector {
    public:
        MyVector() {
            arr = new T[Length];
            size = Length;
        }

        MyVector(const MyVector& from) {
            size = from.size;
            arr = new T[size];
            memcpy(arr, from.arr, size);
        }

        ~MyVector() {
            delete[] arr;
        }

        MyVector& operator =(const MyVector& from) {
            if (&from == this) {
                return *this;
            }

            // What if arr has a different size?
            arr = from.arr;
            size = from.size;
            return *this;

            //arr = new T[from.size];
            //memcpy(arr, from.data, from.size);
        }

    private:
        T* arr;
        int size;
};