# Solutions for exercise sheet 3

## Task 1

The copy- ans move assignments don't get called, but we don't know why. Also there is a bug for one case of the copy assignment in shared_ptr_to_vec2: Less storage gets freed than allocated.

Compile with "g++ -Wall -Wextra -o main main.cpp unique_ptr_to_vec2.cpp shared_ptr_to_vec2.cpp ReferenceCounter.cpp"

#### Valgrind output
==7002==

==7002== HEAP SUMMARY:

==7002==     in use at exit: 0 bytes in 0 blocks

==7002==   total heap usage: 19 allocs, 19 frees, 73,844 bytes allocated

==7002== 

==7002== All heap blocks were freed -- no leaks are possible

==7002== 

==7002== For counts of detected and suppressed errors, rerun with: -v

==7002== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


## Task 2

For the java version:

- install java and javac ( `sudo apt install openjdk-8-jdk-headless`)
- compile using `javac manager.java`
- run with `java manager`
