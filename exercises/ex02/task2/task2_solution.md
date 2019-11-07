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

Compiling with only "g++ -o iterations iterations.cpp" gives no compiler warnings whatsoever. When the resulting program is run we are stuck in an infinite loop. This is expected. 

Compiling with "g++ -Wall -Werror -O2 -o iterations iterations.cpp" doesn't give any compiler warnings either. However when the program is run a segmentation fault occurs instead of the program being stuck in an infinite loop. 