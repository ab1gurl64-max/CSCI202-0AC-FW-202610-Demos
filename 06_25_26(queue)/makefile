all: process.o
	g++ -pedantic-errors -g main.cpp process.o -o main
process.o: process.h process.cpp
	g++ -pedantic-errors process.cpp -g -o process.o -c
clean:
	rm main