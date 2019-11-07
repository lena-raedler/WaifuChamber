## Task 2 (2 Points)

Examine the program `iterations.cpp` and think about the expected output.
Compile the program and run it.
What do you notice?
Did you expect this behaviour?
Did you get any compiler warnings?
Investigate what is actually happening (consider using `valgrind` or a debugger).

How can such errors be prevented?
Look for tools (static code analysers) which help discovering such faulty code.

**Note:** If you run the executable and everything seems normal, try changing the initial content of `xs`, using different optimisation flags, or a different compiler.
The actual behaviour of this executable depends on various factors.

# Solution

Compiling with only "g++ -o iterations iterations.cpp" gives no compiler warnings whatsoever. When the resulting program is run we are stuck in an infinite loop. This is expected. The first for loop runs until our iterator is equal to the end of the traversed vector. However since in each iteration we add one element to the back of the vector we also shift the end of the vector. Therefore we will never reach the end and the program is stuck in an infinite loop. Two exceptions would be if the vector is either empty or has just a single element. 

It also sometimes happens that the program directly terminates with a segmentation fault. However this is inconsistent and most of the time the infinite loop takes over. 

Compiling with "g++ -Wall -Werror -O2 -o iterations iterations.cpp" doesn't give any compiler warnings either. Also we haven't noticed any segmentation faults, only infinite loops. 

[//]: # (However when the program is run a segmentation fault occurs instead of the program being stuck in an infinite loop. )

[//]: # (Compiling with only "g++ -o iterations iterations.cpp" gives no compiler warnings whatsoever. When the program is run a segmentation fault occurs and the program terminates.)
 
[//]: # (Compiling with "g++ -Wall -Werror -O2 -o iterations iterations.cpp" doesn't give any compiler warnings either. However when the resulting program is run, instead of receiving a segmentation fault, we are stuck in an infinite loop. This is expected. The first for loop runs until our iterator is equal to the end of the traversed vector. However since in each iteration we add one element to the back of the vector we also shift the end of the vector. Therefore we will never reach the end and the program is stuck in an infinite loop. Two exceptions would be if the vector is either empty or has just a single element.)
