# Exercise Sheet 5 — More of This and That

*due on 3 December 2019*

## Task 1 (2 Points)

Reuse the `Person` struct and implementation from the previous exercise sheet.
Create 5 difference instances and put all of them in

- an `std::vector`;
- an `std::set`; and
- an `std::map` as key (we don't care about the value type of the map)

Observe which operators are used for insertion.

Use algorithms from the standard library, like `std::find` and `std::partition` on these containers.
Again, observe which operators are used.

## Task 2 (3 Points)

Reuse the `Person` struct and implementation from the previous exercise sheet.
Implement the necessary parts for inserting it into an `std::unordered_set`.

Explore the difference in execution time regarding insertion and lookup for the following containers:

- `std::vector`
- `std::list`
- `std::set`
- `std::unordered_set`

Prepare plots for your presentation.

## Task 3 (2 Points)

In this task you have to create a rudimentary plugin system.

You are given `plugin.hpp` which contains an interface for your plugins, as well as the function name of the constructor function and its type.
Note that the constructor function returns an `std::unique_ptr<Plugin>`.

- Create an executable which *dynamically* loads plugins, instantiates them, and executes their `run` member function
- Create two different plugins (`foo` and `bar`) showing off the plugin system

It could look like this:

    $ ./main ./libFoo.so
    Creation of first plugin
    Running the first plugin
    Destruction of first plugin

    $ ./main ./libFoo.so ./libBar.so
    Creation of first plugin
    Creation of second plugin
    Running the first plugin
    Running the second plugin
    Destruction of first plugin
    Destruction of second plugin

*Hint:* Have a look at the related man-pages *dlopen(3)* and *dlsym(3)*.

*Hint 2:* Use `extern "C"` to have C linkage for the create function.

## Task 4 (6 Points, Bonus, There Be Dragons)

Revisit task 2 of the previous exercise sheet.
This time you are tasked with creating a library that replaces a function inside an executable — rather than one located in another shared library.

The provided program `victim.c` contains a function `func1` which outputs a string.
Your library should replace the function so a different string is printed.

There are multiple ways to approach this.
You may look into hooking frameworks if you are stuck, but do not use them blindly.

*Hint:* Have a look at [this code snippet designed for Linux x86](https://gist.github.com/W4RH4WK/acb16ab57ee95e0ce94d).

*Hint 2:* You may use `-no-pie` for compiling `victim.c` or disable [ASLR](https://en.wikipedia.org/wiki/Address_space_layout_randomization) if you have to.

## Additional Resources

- 🎥 [CppCon 2014 — *Back to the Basics! Essentials of Modern C++ Style*](https://www.youtube.com/watch?v=xnqTKD8uD64)
- 🎥 [CppCon 2019 — *Behind Enemy Lines - Reverse Engineering C++ in Modern Ages*](https://www.youtube.com/watch?v=ZJpvdl_VpSM)
