make shared library using `g++ -fPIC -shared Interceptor.cpp -o Interceptor.so`

create executable using CMakeLists.text

and finally `LD_PRELOAD=$PWD/Interceptor.so ./executable`
