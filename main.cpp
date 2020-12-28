#include <iostream>
#include "./version.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    std::cout << "version: " << GetVersion() << std::endl;

    return 0;
}
