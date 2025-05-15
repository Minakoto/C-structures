CC = g++

all: build

build: menu

menu: menu.o
	$(CC) menu.o -o menu
	rm *.o

menu.o: menu.cpp btree.h
	$(CC) -c menu.cpp
clean:
	rm menu
