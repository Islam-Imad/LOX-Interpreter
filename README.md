# LOX-Interpreter
Implementing a Tree Walk Interpreter.


## How to run
- Clone the repository
- check that cmake is installed on your system
    - Linux
        ```bash
        sudo apt-get install cmake
        ```
    - MacOS
        ```bash
        brew install cmake
        ```
    - Windows
        - Download the installer from [here](https://cmake.org/download/)
- run the following commands
```bash
mkdir build
cd build
cmake ..
make
./lox ../Examples/HelloWorld.lox
```