make shared library using `g++ -fPIC -shared Interceptor.cpp -o Interceptor.so`

create executable using CMakeLists.text

and finally `LD_PRELOAD=$PWD/Interceptor.so ./executable`

if it cant find the symbol use `nm libFoo.so | grep just` and copy the mangled name into the symbol pointer and try again
