#pragma once

#include <memory>
#include <string>
#include "CPU.h"
#include "Memory.h"

class Chip8{
private:
	CHIP_8_MEMORY _memory;
	std::unique_ptr<CPU> _cpu;

	void clearMemory();
	void loadProgram(const std::string& file);
	void loadFontSet();
public:
	Chip8();
	~Chip8();
};