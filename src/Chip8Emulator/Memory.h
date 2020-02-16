#pragma once

#include <cstdint>

static const int CHIP_8_MEMORY_SIZE = 4096;
static const int CHIP_8_EXECUTABLE_ADDRESS = 512;
static const int CHIP_8_FONTSET_ADDRESS = 80;

using byte = uint8_t;
using CHIP_8_MEMORY = byte[4096];