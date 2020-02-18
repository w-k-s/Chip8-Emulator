#pragma once

#include <memory>
#include <string>
#include "CPU.h"
#include "Memory.h"
#include "Window.h"

class Chip8{
private:
	CHIP_8_MEMORY _memory;
	std::unique_ptr<CPU> _cpu;
	std::unique_ptr<Window> _window;

	void clearMemory();
	void loadProgram(const std::string& file);
	void loadFontSet();
public:
	Chip8();
	void run(const std::string& file);
	Chip8(const Chip8&)				= delete;
    void operator=(const Chip8&)	= delete;
	~Chip8();
};