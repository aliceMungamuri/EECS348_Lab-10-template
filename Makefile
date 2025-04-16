all: calculator

calculator: main.o calculator.o
	g++ -o calculator main.o calculator.o

main.o: main.cpp calculator.hpp
	g++ -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	g++ -c calculator.cpp

clean:
	rm -f *.o calculator
