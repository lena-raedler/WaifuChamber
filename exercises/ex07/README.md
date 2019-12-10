# Exercise Sheet 7 — Becoming more meta

*due on 7 January 2020*

## Task 1 (2 Point)

You are given the following definition of a person:

```cpp
struct Person {
    std::string first_name;
    std::string last_name;
    int age;
};
```

Create an `std::vector<std::shared_ptr<Person>>` with at least 3 different instances of `Person`.

Create a function which takes a `const std::vector<std::shared_ptr<Person>>&` as input and returns an `std::vector<Person*>`.
Each element in the result vector corresponds to the respective element in the input vector.

For the functional programming nerds, the definition of this function would be something like `fmap std::shared_ptr::get`.

Write your function in different ways and compare the readability:

- Use a range-based for-loop
- Use `std::transform` with `std::mem_fn`
- Use `std::transform` with a lambda expression

Think about taking the argument by value instead of taking it by const reference.

*Hint:* While not yet available in C++17, take a peek at *ranges*.

## Task 2 (3 Points)

You are given the following code snippet of a mathematical vector.

```cpp
template <std::size_t N>
class Vector {
  public:
    /* ... */

  private:
    std::array<double, N> data;
};
```

Implement the following functions for `Vector`:

- componentwise addition via `operator+`
- `to_string`

Find an elegant way to provide the following interface:

- On default construction (no arguments), all elements are initialised to zero
- Besides copy / move semantics, there is only one additional constructor which takes *exactly* `N` `double`s to initialise `data`
- Accessing elements via the subscript operator `operator[]`
- Members `.x`, `.y`, `.z` access `data[0]`, `data[1]`, `data[2]` respectively
    - With `N == 1` there should be only `.x` available
    - With `N == 2` there should be `.x` and `.y` available
    - With `N == 3` there should be `.x`, `.y`, and `.z` available

Add a few tests to ensure correct behaviour using the following aliases:

```cpp
using Vec1 = Vector<1>;
using Vec2 = Vector<2>;
using Vec3 = Vector<3>;
```

*Note:* You are allowed to modify the given snippet as necessary.

## Task 3 (3 Points)

Revisit the meta programming example from the lecture regarding `std::tuple`.

Given the following class template:

```cpp
template <typename... Types>
class type_set {};
```

`type_set` should behave like a set of types.
The empty set would therefore be `type_set<>`, while the set containing the type `int` would be `type_set<int>`, so on and so forth.

- Create a meta function `type_set_contains_v` which checks if a given `type_set` contains a given type.
- Create a meta function `type_set_is_subset_v` which checks if a given `type_set` is a subset of another given `type_set`.
- Create a meta function `type_set_is_same_v` which checks if a given `type_set` is equal to another given `type_set`.
- Create a meta function `type_set_size_v` which tells the size of a given `type_set`.
  For `type_set<int, int, float>` it should return 2.

Try not to use any of the utilities provided by the standard library (like the example provided in the lecture).

*Hint:* If you are struggling with this exercise you might want to have a look at how *fold* (i.e. *reduce*) is used in functional programming languages.
