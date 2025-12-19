CC=g++
CFLAGS=-c -Wall

all: calculator

calculator: main.o libcalculator.a
	$(CC) main.o -L. -lcalculator -o calculator

libcalculator.a: calculator.o
	ar rcs libcalculator.a calculator.o

calculator.o: calculator.cpp
	$(CC) $(CFLAGS) calculator.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -f *.o *.a calculator
