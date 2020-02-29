
# --- Set Variables

if(APPLE)
    set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/sdl/SDL2.framework/Headers)
	set(SDL2_LIBRARY_NAME ${CMAKE_SOURCE_DIR}/lib/sdl/SDL2.framework)
endif()

# --- Find Sources

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)

find_library(SDL2_LIBRARY_NAME SDL2)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/Chip8Emulator CHIP8_SOURCES) 

set(SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp 
			${CMAKE_SOURCE_DIR}/src/Utilities/logging.h
			${CHIP8_SOURCES})

# --- Build executable

add_executable(Chip8Emulator ${SOURCES})

target_include_directories(Chip8Emulator PRIVATE 
							"${CMAKE_SOURCE_DIR}/src" 
							"${CMAKE_SOURCE_DIR}/src/Utilities"
							"${CMAKE_SOURCE_DIR}/src/Chip8Emulator"
							"${SDL2_INCLUDE_DIR}")

target_link_libraries(Chip8Emulator 
							"${SDL2_LIBRARY_NAME}")

