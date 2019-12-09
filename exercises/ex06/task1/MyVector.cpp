//
// Created by bnorb on 08.12.19.
//

//#include "MyVector.hpp"

template <typename T, int Length>
class MyVector {
    public:
        MyVector() {
            //arr[Length] = {};
            arr = new T[Length];
        }

        ~MyVector() {
            delete[] arr;
        }

    private:
        //T arr[];
        T* arr;
};