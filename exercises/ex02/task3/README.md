# Task 3
## GCC
No issues when compiling with `O0`, however starting with `O1` we begin to see a segfault.
After investigating further, we came to the conclusion that the inner loop never terminates after its first completion.
This is caused by an out of bounds index in line 7
```
for (int i = 0; i <= 5; ++i) {
```
Somehow the iterator variable gets optimized out, and after not returning due to a lucky find of 0 on the first loop, the program is stuck in optimizing hell, also known as O(n^n).
## Clang
Using clang the program worked without issues
