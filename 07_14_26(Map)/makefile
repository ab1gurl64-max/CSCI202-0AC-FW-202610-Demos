all: donut main.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -std=c++20 -fmodules-ts -g main.cpp donut -o main
donut: donut.h donut.cpp
	g++ -pedantic-errors -std=c++20 -g -c donut.cpp -o donut
clean:
	
	rm donut
	rm main