
#include <cstring>
#include <iostream>

template <typename T, int Length>
class MyVector {
    public:
        MyVector() {
            std::cout << "Default constructor" << std::endl;
            arr = new T[Length];
            size = Length;
        }

        MyVector(T* t, int length) {
            std::cout << "Full constructor" << std::endl;
            size = length;
            arr = new T[length];
            memcpy(arr, t, length);
        }

        MyVector(const MyVector& from) {
            std::cout << "Copy constructor" << std::endl;
            size = from.size;
            arr = new T[size];
            memcpy(arr, from.arr, size);
        }

        MyVector(MyVector&& from) {
            std::cout << "Move constructor" << std::endl;
            size = from.size;
            memcpy(arr, from.arr, size);     // No new memory allocated

            from.arr = nullptr;
        }

        MyVector& operator=(const MyVector& from) {
            std::cout << "Copy assignment" << std::endl;
            if (&from == this) {
                return *this;
            }

            // What if arr has a different size?
            size = from.size;
            memcpy(arr, from.arr, size);

            return *this;
        }

        MyVector& operator=(MyVector&& from) {
            std::cout << "Move assignment" << std::endl;
            if (&from == this) {
                return *this;
            }

            size = from.size;
            arr = from.arr;
            from.arr = nullptr;

            return *this;
        }

        ~MyVector() {
            std::cout << "Destructor" << std::endl;
            delete[] arr;
        }

    private:
        T* arr;
        int size;
};