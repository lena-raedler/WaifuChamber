# Exercise Sheet 3 — New Tools in a Familiar Context (cont.)

*due on 19 November 2019*

The C++ language provides a lot of tools, each of them suited for different use cases.
It is paramount to pick the right tool for the right job as well as understanding their limitations.

## Task 1 (4 Points)

This task focuses on the correct implementation of RAII as well as copy and move semantics.
You are asked to implement the concept of `unique_ptr` and `shared_ptr`.
Since we won't concern ourselves with templates for the moment your implementation will *own* an instance of the following `struct`.

```cpp
struct Vec2 {
    float x, y;
};
```

- Read the documentation regarding *smart pointers*, `unique_ptr`, and `shared_ptr`
- Implement your version of `unique_ptr_to_vec2` and `shared_ptr_to_vec2` fulfilling these requirements:
  - *Dynamically* allocate an instance of `Vec2` in your constructor
  - Deallocate the `Vec2` instance in your destructor
  - Implement correct copy semantics (copy constructor / copy assignment)
  - Implement correct move semantics (move constructor / move assignment)
  - Enable access to `Vec2` via the operators `*` and `->`
  - Thread-safety for `shared_ptr_to_vec2`'s reference counter is not required
  - Pay attention to corner-cases like self-assignment (`v = v`)
- Prepare a few interesting test cases for your presentation
- Check your implementation for memory leaks and memory corruptions using `valgrind`

## Task 2 (3 Points)

You are given the following, incomplete definition of a person and a room:

```cpp
struct Person {
    std::string first_name;
    std::string last_name;
    int age;
};

class Room {
  public:
    Room(int id, size_t limit) : id(id), limit(limit) {}

    // Returns true iff the person successfully entered.
    bool enter(/* Person */) {}

    void exit(/* Person */) {}

  private:
    const int id;
    const size_t limit;
    std::vector</* Person */> people;
};
```

`Room` contains a list of people currently located inside.
People can enter and exit the room via the respective member functions.
However, only `limit` people may be inside the room at most, at any given time (invariant).

- Add the missing pieces; pay special attention to the types

The following use cases need to be covered next:
- Asking a `Room` how many people are currently located inside
- Asking a `Room` whether a specific person is currently located inside
- Iterating over all people currently located in a `Room`

Implement whatever is necessary to support these use cases, making sure the invariant remains intact.

How would you solve this exercise in Java?

## Additional Resources

- 🎥 [CppCon 2018 – *OOP is dead, long live Data-oriented design*](https://www.youtube.com/watch?v=yy8jQgmhbAU)
- [Rule of Three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming))
