# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Executable name
TARGET = calculator_program

# Source files
SRCS = main.cpp calculator.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule: Build the program
all: $(TARGET)

# Linking step
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
