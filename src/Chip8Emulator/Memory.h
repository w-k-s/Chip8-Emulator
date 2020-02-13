#pragma once

static const int CHIP_8_MEMORY_SIZE = 4096;
static const int CHIP_8_EXECUTABLE_ADDRESS = 512;
static const int CHIP_8_FONTSET_ADDRESS = 80;

using Memory = unsigned char;
using CHIP_8_MEMORY = unsigned char[4096];