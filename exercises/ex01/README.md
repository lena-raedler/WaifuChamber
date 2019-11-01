# Exercise Sheet 1 — Infrastructure

*due on 5 November 2019*

In this exercise sheet you are asked to set up some infrastructure for developing C++ applications.
The time required for this exercise sheet varies depending on how much experience you have with setting up software and build environments.
If you run into problems consult your fellow students first and contact me if the problem persists.

## Task 1 (2 Points)

Install G++ and Clang, then compile the provided file `hello.cpp`.
Use the following flags when compiling:

    -std=c++17 -Wall -Wextra -O2

If you are a Windows user, you may instead use Visual Studio.
Adjust the compile flags accordingly.
Alternatively, use [WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux).

Next, set up [Boost](http://www.boost.org/) on your system and compile the provided file `hello_boost.cpp`.
Boost is quite common and provides you a set of useful C++ libraries.
Some of its content is even promoted into the C++ standard library.

## Task 2 (2 Points)

Run Clang on the provided file `vec.cpp` using the following command:

    clang -std=c++17 -Xclang -ast-dump -fsyntax-only -Wno-vexing-parse vec.cpp

Clang will parse the input file and display its abstract syntax tree (AST).
In the bottom half of the output you'll find the function declaration of `main` followed by its `CompoundStmt`.
Take a close look at its children and compare the resulting AST with the input code.
Notice any oddities — something that looks counter intuitive?

Sometimes looking at the AST of a C++ program helps to understand what is really going on behind the scenes.
Clang is a useful tool for this purpose.
G++ also provides some mechanisms to dump internal representations, but I find Clang's AST more accessible.

As you can see, there are multiple different ways of initialisation in C++.
Check out the [corresponding section at cppreference](https://en.cppreference.com/w/cpp/language).

## Task 3 (3 Points)

The directory `task3` hosts four subdirectories, `libFoo`, `libBar`, `libBaz`, and `app`.

Each folder prefixed with `lib` represents a shared library and contains a header plus a source file.
Furthermore, the library `libBaz.so` depends on `libBar.so`.

`app` contains a single source file providing a `main` function.
It depends on all three libraries.

![Dependency Graph](images/task3_dependencies.png)

- Model this project structure using [CMake](https://cmake.org/)
- Be sure to set the C++ standard to C++17 and enable warnings (`-Wall -Wextra`)
- The default build type should be *Release*

CMake itself is a build system generator.
You can choose from a variety of target build systems.

- Use `cmake` to generate the actual build system
- Build the project

Take note of the following features:

- *Out of source build*, generated files do not pollute the source directory
- Dependencies of translation-units are automatically obtained

What else do you notice?

## Task 4 (Required)

Send me a mail with your team composition.
If you choose to do a custom side project, also include your side project specification.
Please use the following subject

    703807 - Team Composition / Side Project

📧 [or this link](mailto:alexander.hirsch@uibk.ac.at?subject=703807%20-%20Team%20Composition%20%2f%20Side%20Project)

## Additional Resources

- [Compiler Explorer](https://godbolt.org/)
- [Voltron — debugger UI toolkit](https://github.com/snare/voltron)
- 🎥 [CppCon 2018 — *Simplicity: Not Just For Beginners*](https://www.youtube.com/watch?v=n0Ak6xtVXno)
