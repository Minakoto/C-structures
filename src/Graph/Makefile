CC = g++
HEADERS = GraphForm.h LMGraph.h Aux.h Graph.h

all: main

main: menu

menu: menu.o
	$(CC) menu.o -o menu
	rm *.o

menu.o: menu.cpp
	$(CC) -c menu.cpp

clean:
	rm *.o *.gch menu