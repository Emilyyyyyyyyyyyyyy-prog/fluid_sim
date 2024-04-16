.PHONY: all clean

all: sfml-app

clean:
        rm *.o sfml-app

sfml-app: main.o
        g++ main.o Vector.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

Vector.o: Vector2.h Vector2.cpp
        g++ Vector2.cpp -c -o Vector.o

main.o: main.cpp Vector.o Vector2.h
        g++ main.cpp -c -o main.o
