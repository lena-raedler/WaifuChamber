// Type your code here, or load an example.
#include <iostream>

template<bool VAL>
struct set_bool {
	static constexpr bool value = VAL;
};

struct true_type : set_bool<true> {};
struct false_type : set_bool<false> {};


template <typename... Args>
struct TypeList;

/// first, we need a way to compare two types

template<typename T, typename U>
struct is_same : false_type {};
template<typename T>
struct is_same<T,T> : true_type {};

// We use partial specialization as a condition:
// - by default, types are not the same
// - iff both type arguments are the same ("is_same<T,T>")
//   we inherit from true_type to set our return "::value" to true

template<typename T, typename U>
constexpr int is_same_v = is_same<T, U>::value;


template <typename Head, typename... Rest>
struct TypeList<Head, Rest...>
{
    static constexpr int size();
 //   static_assert(!TailList::template contains<Head>(), "Types must be unique");


};


template<typename T, class Set>
struct set_contains : false_type {
};
// the base case -- we don't have the element

template<class T, class Head, class... Rest>
struct set_contains<T, TypeList<Head, Rest...>> : set_bool<
	is_same_v<Head, T> || set_contains<T, Rest...>::value
> {};

template<typename T, typename U>
constexpr int set_contains_v = set_contains<T, U>::value;

template<typename T, class Set>
struct set_is_subset : true_type {
};

//template <class Head1, class... Rest1, class Head2, class... Rest2>
//struct set_is_subset<TypeList<Head1, Rest1...>, TypeList<Head2, Rest2...>> : set_bool< is_same_v<Head1, Head2> || set_contains<Head1, Rest2...> && set_is_subset<Rest1..., TypeList<Head2, Rest2...>>::value>{};


template<typename T, typename U>
constexpr bool set_is_subset_v = set_is_subset<T, U>::value;


template <typename Head, typename... Rest>
constexpr int TypeList<Head, Rest...>::size()
    {
        return set_contains<Head, Rest...>::value ? 0 : 1 + TypeList<Rest...>::size();
    }

int main(void){
    std::cout << "int is in int, float: " << set_contains_v<int, TypeList<int,float>> << std::endl;
    std::cout << "int is in double, float: " << set_contains_v<int, TypeList<double,float>> << std::endl;
    std::cout << "int int size: " <<TypeList<int, int>::size();
    return 1;
}
