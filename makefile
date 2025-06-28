# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 `sdl2-config --cflags`

# Linker flags
LDFLAGS := `sdl2-config --libs`

# Source and output
SRC := main.cpp Renderer3D.cpp
OBJ := $(SRC:.cpp=.o)
TARGET := engine

# Default target
all: $(TARGET)

# Link objects to create executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp Renderer3D.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)
