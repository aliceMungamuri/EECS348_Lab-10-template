# Makefile for Lab 10 - EECS 348
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = calculator_exec
OBJS = main.o calculator.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp calculator.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	$(CXX) $(CXXFLAGS) -c calculator.cpp

clean:
	rm -f *.o $(TARGET)
