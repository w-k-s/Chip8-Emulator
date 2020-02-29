cmake_minimum_required(VERSION 3.12.2 FATAL_ERROR)
project("Chip-8 Emulator")

# --- Set Variables

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

# Add directories to the end of this directory’s include paths
include_directories(src)

# Include the directory source_dir in your project. 
# This directory must contain a CMakeLists.txt file
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)


# --- Unit testing

#enable_testing()


