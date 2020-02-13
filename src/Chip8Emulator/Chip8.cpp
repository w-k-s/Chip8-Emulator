#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

#include "Chip8.h"
#include "FontSet.h"

Chip8::Chip8()
{
    this->clearMemory();
    this->loadFontSet();

    this->_cpu = std::unique_ptr<CPU>(new CPU { this->_memory });
}

Chip8::~Chip8()
{
}

void Chip8::clearMemory()
{
    std::fill(this->_memory, this->_memory + CHIP_8_MEMORY_SIZE, 0);
}

void Chip8::loadProgram(const std::string& file)
{
    //TODO handle exception

    auto input = std::ifstream { file, std::ios::binary };
    auto inputIterator = std::istreambuf_iterator<char> { input };

    const auto size = CHIP_8_MEMORY_SIZE - CHIP_8_EXECUTABLE_ADDRESS;

    std::copy_n(inputIterator, size, &this->_memory[CHIP_8_EXECUTABLE_ADDRESS]);
}

void Chip8::loadFontSet()
{
    std::copy_n(CHIP_8_FONTSET, CHIP_8_FONTSET_SIZE, &this->_memory[CHIP_8_FONTSET_ADDRESS]);
}