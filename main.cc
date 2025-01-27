#include <iostream>
#include <string>
#include "version.h"
#include "scanner.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Version: " << PROJECT_VERSION << std::endl;
    Scanner scanner("print \"Hello, World!\";");
    return 0;
}