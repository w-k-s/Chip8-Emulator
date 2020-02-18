#include "Chip8Emulator/Chip8Emulator.h"
#include <iostream>
#include <memory>

int main()
{
    auto chip8 = std::make_unique<Chip8>();
    std::cout << sizeof(chip8);
}