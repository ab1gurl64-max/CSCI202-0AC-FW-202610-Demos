all: order donut main.cpp
	g++ -pedantic-errors -g -fdiagnostics-color=always main.cpp donut order -o main
donut: donut.h donut.cpp
	g++ -pedantic-errors -g -c -fdiagnostics-color=always donut.cpp  -o donut
order: donut order.cpp order.h
	g++ -pedantic-errors -g -c -fdiagnostics-color=always order.cpp  -o order
clean:
	rm donut
	rm order
	rm main