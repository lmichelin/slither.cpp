all: build run

build:
	g++ -Wall -std=c++11 -pthread main.cpp -o main.x -lsfml-graphics -lsfml-window -lsfml-system

run:
	./main.x

clean:
	rm -f *.x
