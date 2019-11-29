1. compile all libraries:
    - `g++ -fPIC -shared plugin.hpp -o libPlugin.so`
    - `g++ -fPIC -shared bar.cpp -o bar.so`
    - `g++ -fPIC -shared foo.cpp -o foo.so`

2. compile the main.cpp file
    - `g++ main.cpp -o main -ldl`

3. run the compile main file
    - `./main ./bar.so ./foo.so`
