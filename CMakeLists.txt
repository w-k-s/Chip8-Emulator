cmake_minimum_required(VERSION 3.12.2 FATAL_ERROR)
project("Chip-8 Emulator")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if(APPLE)
    set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/sdl/SDL2.framework/Headers)
	set(SDL2_LIBRARY_NAME ${CMAKE_SOURCE_DIR}/lib/sdl/SDL2.framework)
else
	message(FATAL_ERROR "Unsupported Platform. SDL2 for this platform is not included in the libraries folder"
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)

find_library(SDL2_LIBRARY_NAME SDL2)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/Chip8Emulator CHIP8_SOURCES) 

set(SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp 
			${CMAKE_SOURCE_DIR}/src/Utilities/logging.h
			${CHIP8_SOURCES})

add_executable(Chip8Emulator ${SOURCES})

target_include_directories(Chip8Emulator PRIVATE 
							"${CMAKE_SOURCE_DIR}/src" 
							"${CMAKE_SOURCE_DIR}/src/Utilities"
							"${CMAKE_SOURCE_DIR}/src/Chip8Emulator"
							"${SDL2_INCLUDE_DIR}")

target_link_libraries(Chip8Emulator 
							"${SDL2_LIBRARY_NAME}")

