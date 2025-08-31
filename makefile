# Makefile for StudyBuddy project

# Compiler
CXX = g++
CXXFLAGS = -mconsole -Wall

# Source files
SRC = day1projectcode.cpp day2projectcode.cpp
OBJ = $(SRC:.cpp=.o)

# Executable name
TARGET = StudyBuddy

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean