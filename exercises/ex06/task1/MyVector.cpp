
#include <cstring>
#include <iostream>

template <typename T>
class MyVector {
    public:
        MyVector() {
            std::cout << "Default constructor" << std::endl;
            arr = new T[size];
            offset = 0;
        }

        MyVector(T* t, int length) {
            std::cout << "Full constructor" << std::endl;
            arr = new T[size];
            memcpy(arr, t, sizeof(T)*size);
            offset = length;
        }

        MyVector(const MyVector& from) {
            std::cout << "Copy constructor" << std::endl;
            size = from.size;
            arr = new T[size];
            offset = from.offset;
            memcpy(arr, from.arr, sizeof(T)*size);
        }

        MyVector(MyVector&& from) {
            std::cout << "Move constructor" << std::endl;
            size = from.size;
            offset = from.offset;
            memcpy(arr, from.arr, sizeof(T)*size);     // No new memory allocated

            from.arr = nullptr;
        }

        MyVector& operator=(const MyVector& from) {
            std::cout << "Copy assignment" << std::endl;
            if (&from == this) {
                return *this;
            }

            // What if arr has a different size?
            size = from.size;
            offset = from.offset;
            memcpy(arr, from.arr, sizeof(T)*size);

            return *this;
        }

        MyVector& operator=(MyVector&& from) {
            std::cout << "Move assignment" << std::endl;
            if (&from == this) {
                return *this;
            }

            size = from.size;
            arr = from.arr;
            offset = from.offset;
            from.arr = nullptr;

            return *this;
        }

        //template <class MyVector>
        void prettyPrint() {
            std::cout << "Values: [";
            for (int i = 0; i < offset-1; i++) {
                std::cout << arr[i] << ", ";
            }
            if (offset > 0)
                std::cout << arr[offset-1] << "]" << std::endl;
        }

        ~MyVector() {
            std::cout << "Destructor" << std::endl;
            delete[] arr;
        }

    private:
        T* arr;
        int size = 256;
        int offset;
};