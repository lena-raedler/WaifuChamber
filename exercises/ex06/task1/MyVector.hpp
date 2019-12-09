//
// Created by bnorb on 08.12.19.
//

#pragma one

//namespace MyVector {

template <typename T, int Length>
class MyVector {

public:
    MyVector();

    ~MyVector();

private:
    T arr[];
};

//}