#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

#include "Chip8.h"
#include "FontSet.h"
#include "SDLWindow.h"

Chip8::Chip8()
{
    this->clearMemory();
    this->loadFontSet();

    this->_window = std::make_unique<SDLWindow>("Chip 8 Virtual Machine");
    this->_cpu = std::make_unique<CPU>(this->_memory, *_window);
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

void Chip8::run(const std::string& file)
{
    this->loadProgram(file);
    this->_cpu->run();
}

void Chip8::loadFontSet()
{
    std::copy_n(CHIP_8_FONTSET, CHIP_8_FONTSET_SIZE, &this->_memory[CHIP_8_FONTSET_ADDRESS]);
}