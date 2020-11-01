# Makefile Bar Chart Race

# Project Name
PROJ_NAME = bcr

# Sources files (*.cpp)
CPP_SOURCE = $(wildcard ./src/*.cpp)

# Header files (*.h)
H_SOURCE = $(wildcard ./lib/*h)

# Objects files
OBJ_FILE = $(subst .cpp,.o, $(subst src,bin,$(CPP_SOURCE)))

# Compiler
CC = g++

# Flags for Compiler
CC_FLAGS = -c	\
		   -Wall	\
		   -std=c++11

# Remove Command
RM = rm -rf

# Commands

all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ_FILE) ./bin/main.o
	@ echo 'Building executable file: $@. Compiler: $(CC)'
	$(CC) -o $@ $^
	@ echo ' '
	@ echo 'To run the program use ./$(PROJ_NAME)'

./bin/%.o: ./src/%.cpp ./lib/%.h
	@ echo 'Building $<. Compiler $(CC)'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./bin/main.o: main.cpp $(OBJ_FILE)
	@ echo 'Building $<. Compiler: $(CC)'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p bin

clean:
	@ $(RM) ./bin/*
	@ rm bcr
	@ rmdir bin
