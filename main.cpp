#include "./version.h"

#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    std::cout << "version: " << GetVersion() << std::endl;
    
    return 0;
}
