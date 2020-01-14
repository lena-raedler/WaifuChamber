#include <iostream>

template <class T,class = void>
struct has_print_to : public std::false_type {}; 

template <class T>
struct has_print_to<T, std::void_t<decltype(std::declval<T>().print_to(std::declval<std::ostream&>()))>> : public std::true_type {};

class A{
    public:
    void print_to(std::ostream& o){
       o << "A";
    }
};
class B{};

int main(){
    A a;
    B b;
if constexpr(has_print_to<A>())
    a.print_to(std::cout);

}
