# Solution Exercise Sheet 2

### Task 1
taken from the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)

- avoid `malloc()` and `free()`, they do not support construction and destruction

- avoid calling `new` and `delete`explicitly; any pointer returned by `new` should belong to a resource handle and not to a plain or naked pointer, those could leak the object

- don't try to catch every exception in every function, here meaningful recovery action cannot be taken which leads to complexity and waste; instead let the exception propagate until a function is reached that can handle it

- use `unique_ptr` or `shared_ptr` to represent ownership, they can prevent resource leaks; additionally prefer `unique_ptr` over `shared_ptr` unless ownership should be shared, `unique_ptr` is simpler and more predictable, and also faster

- manage resources automatically using resource handles and RAII to avoid leaks and complex manual resource management; when dealing with paired acquire/release function calls it is advised to encapsulate that resource in an object that already enforces pairing through the constructor and destructor

### Task 2

### Task 3

The program is fine except for one thing: The for loop in contains() loops 6 times over array, though array only has 5 elements, i.e. the last element in array is at the 4th position. If we try to access array[5] we are out of bounds of the array. We do not know what value is stored behind this address and it could change anytime, therefore making the outcome unpredictable. This can be easily fixed by changing the '<=' in the loop condition to a '<'. 

Compiling with "g++ -o strange strange.cpp" does not give any compiler warnings. The program runs fine and on our test machine the output of the 5th array element was always 0. 

Compiling with "g++ -Wall -Werror -o strange strange.cpp" didn't change anything. Valgrind doesn't report any errors or other suspicious activity. 

Compiling with "g++ -Wall -Werror -O2 -o strange strange.cpp" is where things get interesting. In contains() instead of returning to the main function after array[5] has been checked, the program simply continues to check array[6], array[7], ... until it runs out of memory and crashes. In our test run this was always after processing array[943]. 