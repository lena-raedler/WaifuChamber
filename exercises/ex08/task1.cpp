#include <iostream>

template <class T,class = void>
struct has_print_to : public std::false_type {}; 

template <class T>
struct has_print_to<T, std::void_t<decltype(std::declval<T>().print_to(std::declval<std::ostream&>()))>> : public std::true_type {};

template<class T>
constexpr bool has_print_to_v = has_print_to<T>::value;

class A{
    public:
    void print_to(std::ostream& o){
       o << "A";
    }
};

template<class T>
std::enable_if_t<has_print_to_v<T>> dump(T t) {
	t.print_to(std::cerr);
    std::cerr << std::endl;
}
template<class T>
std::enable_if_t<!has_print_to_v<T>> dump(T t) {
	std::cerr << "no print_to here, move along" << std::endl;
}
class B{};

int main(){
    A a;
    B b;

    dump(a);
    dump(b);
    

}
