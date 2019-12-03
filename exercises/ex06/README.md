# Exercise Sheet 6 — Same Same but Different

*due on 10 December 2019*

## Task 1 (4 Points)

Implement your own version of `std::vector` without using any of the provided containers — use *regular arrays* (`new[]` / `delete[]`) to house your elements.
The focus of this task lies on the use of templates.
You do not have to concern yourself with custom allocators and iterators (see task 2).

Test your implementation with different types (`int`, `double`, and a custom struct).

## Task 2 (2 Points)

Take your vector from task 1 and implement iterators.
You might want to read through the respective documentation.

Write some tests utilising algorithms provided by the standard library to check if your iterators behave correctly.

## Task 3 (1 Points)

Take your vector from task 1 and implement iterators.
Instantiate the template at least twice with different types.

Examine the resulting object file using `nm`.

Measure the relationship between compile time and number of unique template instantiations.
Prepare a scatter plot for presentation.

## Task 4 (3 Points)

Read [this blog post](https://www.gamedev.net/blogs/entry/2265481-oop-is-dead-long-live-oop).

Prepare a short summary, paying special attention to the use of templates.
What benefits and drawbacks do you identify?

## Task 5 (2 Points)

Take your vector from task 1 and implement componentwise addition via `operator+` on your vector.
Support implicit type conversions: `MyVector<int>{} + MyVector<double>{}` yields a `MyVector<double>`.

*Hint:* Look into `decltype` and `std::declval`.
