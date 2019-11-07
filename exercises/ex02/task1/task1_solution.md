# Task 1 - C++ Core Guidelines

## I: Interfaces

- avoid non-constant global variables, as they hide dependencies which are then in turn subject to unpredictable changes
- avoid Singletons, they are complicated global objects in disguise
- state preconditions to constrain proper use; some conditions can be expressed as assertions -> use Expects(), also this is preferred
- state postconditions to possibly catch false implementations; this can be done using the Ensure() statement; this is preferred as well
- use exceptions to signal a failure to perform a required task, errors should not have the option to be ignored as this could leave the system in an unexpected state
- never transfer ownership by a raw pointer or reference, leaks of premature destruction could occur, instead pass ownership using a `shared_ptr` or `unique_ptr`, alternatively mark the owning pointer with `owner`
- keep the number of function arguments low, too many arguments is confusing and often more costly -> try to use max 4 but preferred less than 4 parameters


## R: Resource Management

- manage resources automatically using resource handles and RAII to avoid leaks and complex manual resources management; when dealing with paired acquire/release function calls it is advised to encapsulate that resource in an object that already enforces pairing through the constructor and destructor
- raw pointers and raw references are non-owning; either use `unique_ptr` or `shared_ptr` or declare ownership; these could lead to memory leaks
- avoid `malloc()` and `free()`, they do not support construction and destruction
- avoid calling `new` and `delete`explicitly; any pointer returned by `new` should belong to a resource handle and not to a plain or naked pointer, those could leak the object
- always overload matched allocation/deallocation pairs in order to preserve matching operations
- use `unique_ptr` or `shared_ptr` to represent ownership, they can prevent resource leaks; additionally prefer `unique_ptr` over `shared_ptr` unless ownership should be shared, `unique_ptr` is simpler and more predictable, and also faster

## E: Error Handling

- develop an error-handlich strategy early in a design, as consistent and complete strategies for handling errors are resource leaks are hard to add to a system later on
- use exceptions for error handling only, C++ implementations are usually optimized based on the assumption that exceptions are a rare occurence
- design the error-handling strategy around invariants: to use an object it must be in a valid state and to recover from an error every object not destroyed must be in a valid state
- let a constructor establish an invariant, and throw if it cannot
- use RAII to prevent leaks, its the simplest and most systematic way of preventing leaks
- never throw while being the direct owner of an object, that would be a leak
- use purpose-designed user-defined types as esceptions, they are unlikely to clash with other people's exceptions
- don't try to catch every exception in every function, here meaningful recovery action cannot be taken which leads to complexity and waste; instead let the exception propagate until a function is reached that can handle it
- minimize the use of explicit `try`/`catch` as it is verbose and non-trivial uses are error-prone


## T: Templates and Generic Programming

## Pro: Profiles

