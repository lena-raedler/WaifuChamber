make shared library using `g++ -fPIC -shared Interceptor.cpp -o Interceptor.so -ldl`

create executable using CMakeLists.text

and finally `LD_PRELOAD=$PWD/Interceptor.so ./executable`

if it cant find the symbol use `nm libfoo.so | grep just` and copy the mangled name into the symbol pointer and try again


RTLD_LAZY \
Perform lazy binding. Only resolve symbols as the code that references them is executed. If the symbol is never referenced, then it is never resolved. (Lazy binding is only performed for function references; references to variables are always immediately bound when the library is loaded.) 