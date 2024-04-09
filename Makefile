.PHONY: all clean

all: run

clean:
	rm *.o

Vector.o: Vector2D.h Vector2D.cpp
	g++ -c Vector2D.cpp -o Vector.o

main.o: main.cpp Vector.o
	g++ main.cpp Vector.o -o main.o

run: main.o
	g++ main.o -o run -lsfml-graphics -lsfml-window -lsfml-system  
