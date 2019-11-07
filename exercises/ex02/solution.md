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
