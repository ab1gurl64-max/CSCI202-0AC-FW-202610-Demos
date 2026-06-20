all: donut main.cpp
	g++ -pedantic-errors -g main.cpp donut -o main
donut: donut.h donut.cpp
	g++ -pedantic-errors -g -c donut.cpp -o donut
clean:
	rm donut
	rm main