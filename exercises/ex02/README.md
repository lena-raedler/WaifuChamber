# Exercise Sheet 2 — New Tools in a Familiar Context

*due on 12 November 2019*

## Task 1 (4 Points)

Skim over the C++ Core Guidelines and pick 5 rules you find interesting.
Prepare these 5 rules for presentation.
At this point, some things may still be a mystery to you.
Research the yet unknown concepts and techniques mentioned in the C++ Core Guidelines relevant to the bullets you picked.
Be prepared to give a short summary of these concepts and techniques in your presentation so your fellow students can follow.

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

## Task 3 (2 Points)

You are given the program `strange.cpp`.
Compile it with different compilers and optimisation flags.
What do you notice?
What is really happening here?

## Additional Resources

- 🎥 [CppCon 2019 — *Naming is Hard: Let's Do Better*](https://www.youtube.com/watch?v=MBRoCdtZOYg)
- 🎥 [CppCon 2015 — *Give me 15 minutes & I'll change your view of GDB*](https://www.youtube.com/watch?v=PorfLSr3DDI)
- [Iterator Invalidation](https://en.cppreference.com/w/cpp/container#Iterator_invalidation)
- [Undefined Behaviour](https://en.cppreference.com/w/cpp/language/ub)
- [Defining the undefinedness of C](https://dl.acm.org/citation.cfm?id=2737979)
- [It's Time To Do CMake Right](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right)
