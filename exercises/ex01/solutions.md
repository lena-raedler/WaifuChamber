# Exercise Sheet 1 - Solution

## Task 1

```
sudo apt-get install g++
sudo apt-get install libboost-all-dev
```

a)

```
g++ -std=c++17 -Wall -Wextra -02 -o hello hello.cpp
```

no issues here

b)

```
g++ -std=c++17 -Wall -Wextra -02 -o hello_boost hello_boost.cpp
```

no issues here

## Task 2

`clang -std=c++17 -Xclang -ast-dump -fsyntax-only -Wno-vexing-parse vec.cpp`

The output of this can be found [HERE](AST.txt).

> Notice any oddities -- something that looks counter intuitive?

```
|-DeclStmt 0x56128f7e85b0 <line:15:2, col:11>
  | `-FunctionDecl 0x56128f7e8500 parent 0x56128f7806a8 <col:2, col:10> col:7 v1 'Vec3 ()'
```

Line 15 is treated as a function declaration, which is also show in the above shown part of the AST. Due to this the variable v1 is not of type Vec3, thus for example the assignment of another value, i.e. `v1 = v3` is not possible.
