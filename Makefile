CXX = g++
CFLAGS = -Wall -c
CXXFLAGS = -g -std=c++17 -Wall -pedantic

OUTPUTDIR = ./bin/
MKDIR = mkdir -p $(OUTPUTDIR)
OBJECTC = *.o
BINARY_NAME = Chip8Emulator

CXXSOURCES = \
	src/*.cpp \
	src/**/*.cpp \


all: main

main: Makefile
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(CXXSOURCES) -o $(OUTPUTDIR)$(BINARY_NAME)

.PHONY: clean
clean:
	$(RM) -rf $(OUTPUTDIR)
	$(RM) ./*.gc??
	$(RM) ./*.o

format:
	clang-format -i -style=WebKit src/*.cpp $(CXXSOURCES)