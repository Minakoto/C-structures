CC = g++

all: build

build: menu

menu: menu.o
	$(CC) menu.o -o menu
	rm *.o

menu.o: menu.cpp clvector.h
	$(CC) -c menu.cpp
