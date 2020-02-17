#include "Chip8Emulator/Chip8Emulator.h"
#include <iostream>
#include <memory>

int main()
{
    auto chip8 = std::unique_ptr<Chip8> { new Chip8 {} };
    std::cout << sizeof(chip8);
}