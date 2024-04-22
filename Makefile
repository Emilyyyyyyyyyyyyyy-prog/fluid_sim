.PHONY: all clean

all: sfml-app

clean: 
	rm *.o sfml-app

sfml-app: main.o Fluid.o Field.o
	g++ main.o Fluid.o Field.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system 

Field.o: Field.cpp Field.h
	g++ -c Field.cpp -o Field.o

Fluid.o: Fluid.cpp Fluid.h Field.o Field.h
	g++ -c Fluid.cpp Field.o -o Fluid.o

main.o: main.cpp Fluid.o
	g++ -c main.cpp -o main.o

