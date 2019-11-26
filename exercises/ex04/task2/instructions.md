make shared library using `g++ -fPIC -shared Interceptor.cpp -o Interceptor.so -ldl`

create executable using CMakeLists.text

and finally `LD_PRELOAD=$PWD/Interceptor.so ./executable`

if it cant find the symbol use `nm libfoo.so | grep just` and copy the mangled name into the symbol pointer and try again
