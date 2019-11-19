# Exercise Sheet 4 — Class Essentials and Libraries

*due on 26 November 2019*

## Task 1 (4 Points)

You are given the following definition of a person:

```cpp
struct Person {
    std::string first_name;
    std::string last_name;
    int age;
};
```

- Implement comparison operators: `==` and `!=`
- Implement relational operators: `<`, `<=`, `>`, and `>=`
- Implement the operator `<<` for `std::ostream`, so we can write:

  ```cpp
  std::cout << Person{"John", "Doe", 42} << std::endl;
  ```

- For primitive types a function `std::to_string` is provided in the standard library.
  Implement a similar function `to_string` for `Person`.

Justify whether your function / operator is a regular function, regular member function, static member function, friend function.

- Put your whole implementation (including `to_string`) in a namespace (eg `foo`).
  Explain why this is possible without `using namespace foo`:

  ```cpp
  foo::Person p1{"John", "Smith", 42};
  std::cout << to_string(p1) << std::endl;
  ```

## Task 2 (3 Points)

The folder `task2` contains code and build instructions for a shared library and an executable which uses the shared library.
The shared library features two functions `random_number` and `just_a_print` inside the `foo` namespace.

Your task is to create an *interceptor* library:

- `random_number` should be replaced with a function that always returns `4` for improved determinism
- `just_a_print` should be wrapped so that some text is printed before and after the original function is executed

Running the executable with and without the interceptor library could look like this:

```
$ ./executable
Random Number: 880806932

Just a print to stdout, nothing else

$ LD_PRELOAD=$PWD/interceptor.so ./executable
Random Number: 4

some text before
Just a print to stdout, nothing else
some text after
```

*Hint:* For Linux, have a look at the related man-pages like *ld-linux(8)*.

## Inday Students

This year's Inday Students event is scheduled for 26 November.
Let me know if you cannot attend the PS because of this.
