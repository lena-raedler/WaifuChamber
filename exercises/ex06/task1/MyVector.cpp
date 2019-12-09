
#include <cstring>
#include <iostream>

template <typename T>
class MyVector {
    public:
        MyVector() {
            //std::cout << "Default constructor" << std::endl;
            arr = new T[maxSize];
            offset = 0;
        }

        MyVector(T* t, int length) {
            //std::cout << "Full constructor" << std::endl;
            arr = new T[maxSize];
            memcpy(arr, t, sizeof(T)*length);
            //memcpy(arr, t, sizeof(T)*maxSize);
            offset = length;
        }

        /*
        MyVector(std::initializer_list<T> l) {
            int count = 0;
            for (T t : l) {
                arr[count++] = t;
            }
            offset = l.size();
        }
         */

        MyVector(const MyVector& from) {
            std::cout << "Copy constructor" << std::endl;
            maxSize = from.maxSize;
            arr = new T[maxSize];
            offset = from.offset;
            memcpy(arr, from.arr, sizeof(T)*maxSize);
        }

        MyVector(MyVector&& from) {
            std::cout << "Move constructor" << std::endl;
            maxSize = from.maxSize;
            offset = from.offset;
            memcpy(arr, from.arr, sizeof(T)*maxSize);     // No new memory allocated

            from.arr = nullptr;
        }

        MyVector& operator=(const MyVector& from) {
            std::cout << "Copy assignment" << std::endl;
            if (&from == this) {
                return *this;
            }

            // What if arr has a different maxSize?
            maxSize = from.maxSize;
            offset = from.offset;
            memcpy(arr, from.arr, sizeof(T)*maxSize);

            return *this;
        }

        MyVector& operator=(MyVector&& from) {
            std::cout << "Move assignment" << std::endl;
            if (&from == this) {
                return *this;
            }

            maxSize = from.maxSize;
            arr = from.arr;
            offset = from.offset;
            from.arr = nullptr;

            return *this;
        }

        ~MyVector() {
            //std::cout << "Destructor" << std::endl;
            delete[] arr;
        }

        // Element access
        T& at(int pos) {
            if (pos < 0 || offset <= pos)
                throw std::out_of_range("Out of range");
            return arr[pos];
        }
        T& operator[](int pos) {
            return arr[pos];
        }
        T& front() {
            return arr[0];  // CppReference: Calling front on an empty container is undefined.
        }
        T& back() {
            return arr[offset-1];   // CppReference: Calling back on an empty container is undefined.
        }

        // Capacity
        bool empty() const {
            return offset <= 0;
        }
        int size() const {
            return offset;
        }
        int max_size() const {
            return maxSize;
        }

        // Modifiers
        void clear() {
            offset = 0;
        }
        void push_back(const T& value) {
            arr[offset++] = value;
        }
        void pop_back() {
            if (offset > 0)     // CppReference: Calling pop_back on an empty container is undefined.
                offset--;
        }

        // TODO Replace int with iterator for ex02
        void erase(const int pos) {
            if (pos < 0 || offset <= pos)
                return;

            for (int i = pos; i < offset-1; i++) {
                arr[i] = arr[i+1];
            }
            offset--;
        }

        // Other functions
        void prettyPrint() {
            std::cout << "Values: [";

            if (offset <= 0) {
                std::cout << "]" << std::endl;
                return;
            }

            for (int i = 0; i < offset-1; i++) {
                std::cout << arr[i] << ", ";
            }
            std::cout << arr[offset-1] << "]" << std::endl;
        }

        //void test() {
        //    MyVector<T>::iterator it;

        //}


        //template <T> class iterator{

        //};


        // Iterator for task 2
        template <T*>
        class iterator2 : public std::iterator<
                std::input_iterator_tag,   // iterator_category
                T,                         // value_type
                ptrdiff_t ,                // difference_type
                const T*,                  // pointer
                const T&                   // reference
                >
        {
            long num = 0;

            //public:
                //iterator2 begin() {
                //    return iterator2(arr[0]);
                //}
        };

        /*
        template <T*>
        iterator2 begin() {
            //return iterator2(arr[0]);
            return iterator2(arr);
        }
         */




    private:
        T* arr;
        int maxSize = 256;
        int offset;     // = number of elements currently stored
};