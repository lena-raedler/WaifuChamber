# Solution Exercise Sheet 2

### Task 1
taken from the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)

- avoid `malloc()` and `free()`, they do not support construction and destruction; its error prone to use `free()` as it can simply be overlooked or forgotten, and for `malloc()` we have to check if it worked --> clumpy and ugly memory management

- avoid calling `new` and `delete` explicitly; any pointer returned by `new` should belong to a resource handle and not to a plain or naked pointer, those could leak the object --> lead to error-prone code; instead use `unique_ptr` or `shared_ptr`

- don't try to catch every exception in every function, here meaningful recovery action cannot be taken which leads to complexity and waste; instead let the exception propagate until a function is reached that can handle it;

- use `unique_ptr` or `shared_ptr` to represent ownership, they can prevent resource leaks; additionally prefer `unique_ptr` over `shared_ptr` unless ownership should be shared, `unique_ptr` is simpler and more predictable, and also faster

- manage resources automatically using resource handles and RAII to avoid leaks and complex manual resource management; when dealing with paired acquire/release function calls it is advised to encapsulate that resource in an object that already enforces pairing through the constructor and destructor

### Task 2

Compiling with only "g++ -o iterations iterations.cpp" gives no compiler warnings whatsoever. When the resulting program is run we are stuck in an infinite loop. This is expected. The first for loop runs until our iterator is equal to the end of the traversed vector. The inner loop adds n elements to the end of the vector where n = the current processed element. This again increases the vector size and the loop condition `it != xs.end()` will always be fulfilled. Therefore we will never reach the end and the program is stuck in an infinite loop. Two exceptions would be if the vector is either empty or has just 0's as elements, in which case the inner loops does not add any more elements to the end of the vector. 

It also sometimes happens that the program directly terminates with a segmentation fault. This happens mostly the first time the program is run after the compilation. However this is inconsistent and more often then not the infinite loop is prevalent. 

Compiling with "g++ -Wall -Werror -O2 -o iterations iterations.cpp", or O3 instead of O2, doesn't give any compiler warnings either. 

Using -O2 or -O3 and no segmentation faul is given the program aborts with the message `terminate called after throwing an instance of std::bad_alloc`

### Task 3

The program is fine except for one thing: The for loop in contains() loops 6 times over array, though array only has 5 elements, i.e. the last element in array is at the 4th position. If we try to access array[5] we are out of bounds of the array. We do not know what value is stored behind this address and it could change anytime, therefore making the outcome unpredictable. This can be easily fixed by changing the '<=' in the loop condition to a '<'. 

#### GCC
Compiling with "g++ -Wall -Werror -o strange strange.cpp" does not give any compiler warnings. The program runs fine and on our test machine the output of the 5th array element was always 0.  Valgrind doesn't report any errors, leaks or other suspicious activity. 

However starting with "g++ -Wall -Werror -O1 -o strange strange.cpp" is where things get interesting. In contains() instead of returning to the main function after array[5] has been checked, the program simply continues to check array[6], array[7], ... until it runs out of memory and crashes. In our test run this was always after processing array[943]. Valgrind obviously crashes too and reports one error. 

Somehow the iterator variable gets optimized out, and after not returning due to a lucky find of 0 on the first loop, the program is stuck in optimizing hell, also known as O(n^n).

#### Clang
Using clang the program worked without issues
