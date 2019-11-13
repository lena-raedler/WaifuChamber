//
// Created by bnorb on 13.11.19.
//

#ifndef APP_MY_UNIQUE_PTR_HPP
#define APP_MY_UNIQUE_PTR_HPP

struct Vec2 {
    float x, y;
};

class unique_ptr_to_vec2 {

public:
    unique_ptr_to_vec2(int x, int y);
    ~unique_ptr_to_vec2();
    void print();

private:
    Vec2 vec2;
};


#endif //APP_MY_UNIQUE_PTR_HPP
